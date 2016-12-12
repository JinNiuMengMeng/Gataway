#include "serial_config.h"

pthread_t thread_poll[2];
pthread_mutex_t mut_read;
pthread_mutex_t mut_write;

extern int g_fd;

//串口结构

/*******************************************
 *  波特率转换函数（请确认是否正确）
********************************************/
int convbaud(unsigned long int baudrate) {
	switch(baudrate) {
	case 2400:
		return B2400;
	case 4800:
		return B4800;
	case 9600:
		return B9600;
	case 19200:
		return B19200;
	case 38400:
		return B38400;
	case 57600:
		return B57600;
	case 115200:
		return B115200;
	default:
		return B9600;
	}
}

/*******************************************
 *  Setup comm attr
 *  fdcom: 串口文件描述符，pportinfo: 待设置的端口信息（请确认）
 *
********************************************/
int PortSet(int fdcom, const pportinfo_t pportinfo) {
	struct termios termios_old, termios_new;
	int     baudrate, tmp;
	char    databit, stopbit, parity, fctl;

	bzero(&termios_old, sizeof(termios_old));
	bzero(&termios_new, sizeof(termios_new));
	cfmakeraw(&termios_new);
	tcgetattr(fdcom, &termios_old);         //get the serial port attributions
	/*------------设置端口属性----------------*/
	//baudrates
	baudrate = convbaud(pportinfo -> baudrate);
	cfsetispeed(&termios_new, baudrate);        //填入串口输入端的波特率
	cfsetospeed(&termios_new, baudrate);        //填入串口输出端的波特率
	termios_new.c_cflag |= CLOCAL;          //控制模式，保证程序不会成为端口的占有者
	termios_new.c_cflag |= CREAD;           //控制模式，使能端口读取输入的数据

	// 控制模式，flow control
	fctl = pportinfo-> fctl;
	switch(fctl) {
	case '0': {
		termios_new.c_cflag &= ~CRTSCTS;        //no flow control
	}
	break;
	case '1': {
		termios_new.c_cflag |= CRTSCTS;         //hardware flow control
	}
	break;
	case '2': {
		termios_new.c_iflag |= IXON | IXOFF |IXANY; //software flow control
	}
	break;
	}

	//控制模式，data bits
	termios_new.c_cflag &= ~CSIZE;      //控制模式，屏蔽字符大小位
	databit = pportinfo -> databit;
	switch(databit) {
	case '5':
		termios_new.c_cflag |= CS5;
	case '6':
		termios_new.c_cflag |= CS6;
	case '7':
		termios_new.c_cflag |= CS7;
	default:
		termios_new.c_cflag |= CS8;
	}

	//控制模式 parity check
	parity = pportinfo -> parity;
	switch(parity) {
	case '0': {
		termios_new.c_cflag &= ~PARENB;     //no parity check
	}
	break;
	case '1': {
		termios_new.c_cflag |= PARENB;      //odd check
		termios_new.c_cflag &= ~PARODD;
	}
	break;
	case '2': {
		termios_new.c_cflag |= PARENB;      //even check
		termios_new.c_cflag |= PARODD;
	}
	break;
	}

	//控制模式，stop bits
	stopbit = pportinfo -> stopbit;
	if(stopbit == '2') {
		termios_new.c_cflag |= CSTOPB;  //2 stop bits
	} else {
		termios_new.c_cflag &= ~CSTOPB; //1 stop bits
	}

	//other attributions default
	termios_new.c_oflag &= ~OPOST;          //输出模式，原始数据输出
	termios_new.c_cc[VMIN]  = 1;            //控制字符, 所要读取字符的最小数量
	termios_new.c_cc[VTIME] = 1;            //控制字符, 读取第一个字符的等待时间unit: (1/10)second

	tcflush(fdcom, TCIFLUSH);               //溢出的数据可以接收，但不读
	tmp = tcsetattr(fdcom, TCSANOW, &termios_new);
//	tmp = tcsetattr(fdcom, TCSADRAIN, &termios_new);
	//设置新属性，TCSANOW：所有改变立即生效    tcgetattr(fdcom, &termios_old);
	return(tmp);
}

void *thread_write() {
	pthread_mutex_lock(&mut_write);
	sendCmdToSerial();
	pthread_mutex_unlock(&mut_write);
	pthread_exit(NULL);
}

void *thread_read() {
	pthread_mutex_lock(&mut_read);
	readcom();
	pthread_mutex_unlock(&mut_read);
	pthread_exit(NULL);
}

void thread_create_serial(void) {
	int temp;
	memset(&thread_poll, 0, sizeof(thread_poll));
	if((temp = pthread_create(&thread_poll[1], NULL, thread_read, NULL)) != 0) {
		printf("thread_read to failed\n");
		exit(0);
	}

	sleep(1);

	if((temp = pthread_create(&thread_poll[0], NULL, thread_write, NULL)) != 0) {
		printf("thread_write to failed\n");
		exit(0);
	}
}

void thread_wait_serial(void) {
	if(thread_poll[0] != 0) {
		pthread_join(thread_poll[0], NULL);
		printf("thread_write stoped\n");
	}
	if(thread_poll[1] != 0) {
		pthread_join(thread_poll[1], NULL);
		printf("thread_read stoped\n");
	}

}


void Gateway_Poll(void) {

	printf("Start Gateway Poll !!!...\n\n");

	portinfo_t portinfo = {
		'0',       // print prompt after receiving
		9600,      // baudrate: 9600
		'8',       // databit: 8
		'0',       // debug: off
		'0',       // echo: off
		'2',       // flow control: software
		'0',       // parity: none
		'1',       // stopbit: 1
		0          // reserved
	};

	g_fd = open("/dev/ttyS1", O_RDWR | O_NOCTTY | O_NONBLOCK);
	if(g_fd<0) {
		printf("Open Com failed,exit!\n");
		exit(1);
	}
	portinfo.baudrate = 9600;
	PortSet(g_fd, &portinfo);

	pthread_mutex_init(&mut_read, NULL);
	pthread_mutex_init(&mut_write, NULL);
	thread_create_serial();
	thread_wait_serial();
	close(g_fd);

	exit(0);

}
