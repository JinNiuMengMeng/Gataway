#include "commend.h"
#include "print.h"

extern int TotalNum;
//extern int sockfd;
//extern uint8_t TotalNum_buf[2];
extern int  i_u, j_u, k_u, l_u, m_u, n_u;
extern double  Current;
extern double  Voltage;
extern double  Active_power;
extern double  Electricity_Quantity;
extern int  Fault_type;
extern uint32_t  Leakage_current;
extern uint32_t  Temperature;

extern double  Current_01;
extern double  Voltage_01;
extern double  Active_power_01;
extern double  Electricity_Quantity_01;
extern int  Fault_type_01;
extern uint32_t  Leakage_current_01;
extern uint32_t  Temperature_01;

extern double  Current_02;
extern double  Voltage_02;
extern double  Active_power_02;
extern double  Electricity_Quantity_02;
extern int Fault_type_02;
extern uint32_t  Leakage_current_02;
extern uint32_t Temperature_02;

extern double  Current_03;
extern double  Voltage_03;
extern double  Active_power_03;
extern double  Electricity_Quantity_03;
extern int Fault_type_03;
extern uint32_t Leakage_current_03;
extern uint32_t Temperature_03;

extern double  Current_04;
extern double  Voltage_04;
extern double  Active_power_04;
extern double  Electricity_Quantity_04;
extern int Fault_type_04;
extern uint32_t Leakage_current_04;
extern uint32_t Temperature_04;

extern double  Current_05;
extern double  Voltage_05;
extern double  Active_power_05;
extern double  Electricity_Quantity_05;
extern int Fault_type_05;
extern uint32_t Leakage_current_05;
extern uint32_t Temperature_05;

extern double  Current_06;
extern double  Voltage_06;
extern double  Active_power_06;
extern double  Electricity_Quantity_06;
extern int Fault_type_06;
extern uint32_t Leakage_current_06;
extern uint32_t Temperature_06;

extern double  upload_Current_01;
extern double  upload_Voltage_01;
extern double  upload_Active_power_01;
extern double  upload_Electricity_Quantity_01;
extern double  upload_Leakage_current_01;
extern double  upload_Temperature_01;

extern double  upload_Current_02;
extern double  upload_Voltage_02;
extern double  upload_Active_power_02;
extern double  upload_Electricity_Quantity_02;
extern double  upload_Leakage_current_02;
extern double  upload_Temperature_02;

extern double  upload_Current_03;
extern double  upload_Voltage_03;
extern double  upload_Active_power_03;
extern double  upload_Electricity_Quantity_03;
extern double  upload_Leakage_current_03;
extern double  upload_Temperature_03;

extern double  upload_Current_04;
extern double  upload_Voltage_04;
extern double  upload_Active_power_04;
extern double  upload_Electricity_Quantity_04;
extern double  upload_Leakage_current_04;
extern double  upload_Temperature_04;

extern double  upload_Current_05;
extern double  upload_Voltage_05;
extern double  upload_Active_power_05;
extern double  upload_Electricity_Quantity_05;
extern double  upload_Leakage_current_05;
extern double  upload_Temperature_05;

extern double  upload_Current_06;
extern double  upload_Voltage_06;
extern double  upload_Active_power_06;
extern double  upload_Electricity_Quantity_06;
extern double  upload_Leakage_current_06;
extern double  upload_Temperature_06;

int getnum(uint8_t* s) {
	if(!strcmp(s,"01")) return 1;
	if(!strcmp(s,"02")) return 2;
	if(!strcmp(s,"03")) return 3;
	if(!strcmp(s,"04")) return 4;
	if(!strcmp(s,"05")) return 5;
	if(!strcmp(s,"06")) return 6;

	return -1;
}

uint8_t * get_zc_buffer(uint8_t *buffer) {

	static uint8_t zc_buf[N] = {0}; // 1.registered

	uint8_t buf[25] = {0};
	strcpy(buf, "#0000#7.1.1#000000#0021#\0");
	uint8_t *Mac_sp = buffer;

	memcpy(zc_buf, "#zc#0101#", 9);
	memcpy(zc_buf + 9, Mac_sp, 16);
	memcpy(zc_buf + 25, buf, 26);

	//	printf("zc_buf: %s\n", zc_buf);
	return zc_buf;
}

void get_sz_buffer(uint8_t *sp, uint8_t *buffer) {
	/*Decryption buf:0101#000000606EA50D2C#02SB#7.1.1#000000#0021#02SB#04#
	#sz#时间戳+数值#分帧号#网关识别码#设备类型码#程序版本号#指令序号#指令类型#
	例：
	#sz#时间戳+数值#0101#0000112233445566#00SB#6.0.0#000000#0022#
	*/
	memcpy(buffer, "#sz#0101#", 9);
	memcpy(buffer + 9, sp + 5, 34);
	memcpy(buffer + 43, "#0022#", 6);

	buffer[strlen(buffer)] = '\0';
}

void Read_A_Single_Device(uint8_t *buffer, uint8_t *rs_buf) {		//"0023"
	uint8_t encryption_buff[N] = {0};
	uint8_t UEBZ[4] = {0};
	uint8_t buf_V[50] = {0};
	uint8_t buf_C[50] = {0};
	uint8_t buf_A[50] = {0};
	uint8_t buf_E[50] = {0};
	uint8_t buf_T[4] = {0};
	uint8_t buf_F[2] = {0};

	memcpy(UEBZ, buffer+45, 2);
	UEBZ[strlen(UEBZ)] = '\0';

	switch (getnum(UEBZ)) {
	case 1:
		flo_to_str_V(Voltage_01, buf_V, 1);
		flo_to_str(Current_01, buf_C, 3);
		flo_to_str(Active_power_01/1000, buf_A, 4);
		flo_to_str(Electricity_Quantity_01, buf_E, 2);
		sprintf(buf_T, "%d", Temperature_01);
		sprintf(buf_F, "%02d", Fault_type_01);

		strcat(rs_buf, "#rs#");
		memcpy(rs_buf+4, buffer, 48);
		strcat(rs_buf, buf_V);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F);
		strcat(rs_buf, "#");
		
		rs_buf[strlen(rs_buf)] = '\0';
		printf("rs_buf:%s\n", rs_buf);
		break;
		
	case 2:
		flo_to_str_V(Voltage_02, buf_V, 1);
		flo_to_str(Current_02, buf_C, 3);
		flo_to_str(Active_power_02/1000, buf_A, 4);
		flo_to_str(Electricity_Quantity_02, buf_E, 2);
		sprintf(buf_T, "%d", Temperature_02);
		sprintf(buf_F, "%02d", Fault_type_02);
		strcat(rs_buf, "#rs#");		
		memcpy(rs_buf+4, buffer, 48);
		strcat(rs_buf, buf_V);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F);
		strcat(rs_buf, "#");
		
		rs_buf[strlen(rs_buf)] = '\0';
		printf("rs_buf:%s\n", rs_buf);
		break;
		
	case 3:
		flo_to_str_V(Voltage_03, buf_V, 1);
		flo_to_str(Current_03, buf_C, 3);
		flo_to_str(Active_power_03/1000, buf_A, 4);
		flo_to_str(Electricity_Quantity_03, buf_E, 2);
		sprintf(buf_T, "%d", Temperature_03);
		sprintf(buf_F, "%02d", Fault_type_03);
		printf("buffer:%s\n", buffer);
		strcat(rs_buf, "#rs#");
		memcpy(rs_buf+4, buffer, 48);
		strcat(rs_buf, buf_V);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F);
		strcat(rs_buf, "#");
		
		rs_buf[strlen(rs_buf)] = '\0';
		printf("rs_buf:%s\n", rs_buf);
		break;
		
	case 4:
		flo_to_str_V(Voltage_04, buf_V, 1);
		flo_to_str(Current_04, buf_C, 3);
		flo_to_str(Active_power_04/1000, buf_A, 4);
		flo_to_str(Electricity_Quantity_04, buf_E, 2);
		sprintf(buf_T, "%d", Temperature_04);
		sprintf(buf_F, "%02d", Fault_type_04);

		strcat(rs_buf, "#rs#");
		memcpy(rs_buf+4, buffer, 48);
		strcat(rs_buf, buf_V);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F);
		strcat(rs_buf, "#");
		
		rs_buf[strlen(rs_buf)] = '\0';
		printf("rs_buf:%s\n", rs_buf);
		break;
	case 5:
		flo_to_str_V(Voltage_05, buf_V, 1);
		flo_to_str(Current_05, buf_C, 3);
		flo_to_str(Active_power_05/1000, buf_A, 4);
		flo_to_str(Electricity_Quantity_05, buf_E, 2);
		sprintf(buf_T, "%d", Temperature_05);
		sprintf(buf_F, "%02d", Fault_type_05);

		strcat(rs_buf, "#rs#");
		memcpy(rs_buf+4, buffer, 48);
		strcat(rs_buf, buf_V);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F);
		strcat(rs_buf, "#");
		
		rs_buf[strlen(rs_buf)] = '\0';
		printf("rs_buf:%s\n", rs_buf);
		break;
		
	case 6:
		flo_to_str_V(Voltage_06, buf_V, 1);
		flo_to_str(Current_06, buf_C, 3);
		flo_to_str(Active_power_06/1000, buf_A, 4);
		flo_to_str(Electricity_Quantity_06, buf_E, 2);
		sprintf(buf_T, "%d", Temperature_06);
		sprintf(buf_F, "%02d", Fault_type_06);

		strcat(rs_buf, "#rs#");
		memcpy(rs_buf+4, buffer, 48);
		strcat(rs_buf, buf_V);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F);
		strcat(rs_buf, "#");
		
		rs_buf[strlen(rs_buf)] = '\0';
		printf("rs_buf:%s\n", rs_buf);
		break;
		
	default:
		break;
	}
}

void Read_All_Device(uint8_t *buffer, uint8_t *rs_buf) {		//"0024"
printf("TotalNum:%d\n", TotalNum);
	switch (TotalNum) {
	case 1: {
		uint8_t buf_V_01[50] = {0};
		uint8_t buf_C_01[50] = {0};
		uint8_t buf_A_01[50] = {0};
		uint8_t buf_E_01[50] = {0};
		uint8_t buf_T_01[4] = {0};
		uint8_t buf_F_01[2] = {0};

		flo_to_str_V(Voltage_01, buf_V_01, 1);
		flo_to_str(Current_01, buf_C_01, 3);
		flo_to_str(Active_power_01/1000, buf_A_01, 4);
		flo_to_str(Electricity_Quantity_01, buf_E_01, 2);
		sprintf(buf_T_01, "%d", Temperature_01);
		sprintf(buf_F_01, "%02d", Fault_type_01);

		strcat(rs_buf, "#rs#");
		strcat(rs_buf, buffer);
		strcat(rs_buf, "01#01;");
		strcat(rs_buf, buf_V_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F_01);

		strcat(rs_buf, "#");
		rs_buf[strlen(rs_buf)] = '\0';
		printf("rs_buf:%s\n", rs_buf);
		break;}
	
	case 2: {
		uint8_t buf_V_01[50] = {0};
		uint8_t buf_C_01[50] = {0};
		uint8_t buf_A_01[50] = {0};
		uint8_t buf_E_01[50] = {0};
		uint8_t buf_T_01[4] = {0};
		uint8_t buf_F_01[2] = {0};

		flo_to_str_V(Voltage_01, buf_V_01, 1);
		flo_to_str(Current_01, buf_C_01, 3);
		flo_to_str(Active_power_01/1000, buf_A_01, 4);
		flo_to_str(Electricity_Quantity_01, buf_E_01, 2);
		sprintf(buf_T_01, "%d", Temperature_01);
		sprintf(buf_F_01, "%02d", Fault_type_01);

		uint8_t buf_V_02[50] = {0};
		uint8_t buf_C_02[50] = {0};
		uint8_t buf_A_02[50] = {0};
		uint8_t buf_E_02[50] = {0};
		uint8_t buf_T_02[4] = {0};
				uint8_t buf_T1_02[4] = {0};
		uint8_t buf_F_02[2] = {0};

		flo_to_str_V(Voltage_02, buf_V_02, 1);
		flo_to_str(Current_02, buf_C_02, 3);
		flo_to_str(Active_power_02/1000, buf_A_02, 4);
		flo_to_str(Electricity_Quantity_02, buf_E_02, 2);
		sprintf(buf_T_02, "%d", Temperature_02);
		sprintf(buf_F_02, "%02d", Fault_type_02);

		strcat(rs_buf, "#rs#");
		strcat(rs_buf, buffer);
		strcat(rs_buf, "02#01;");
		strcat(rs_buf, buf_V_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F_01);

		strcat(rs_buf, "#02;");
		strcat(rs_buf, buf_V_02);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C_02);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A_02);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E_02);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T_02);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F_02);

		strcat(rs_buf, "#");
		rs_buf[strlen(rs_buf)] = '\0';
		printf("rs_buf:%s\n", rs_buf);
		break;}
	
	case 3: {
		uint8_t buf_V_01[50] = {0};
		uint8_t buf_C_01[50] = {0};
		uint8_t buf_A_01[50] = {0};
		uint8_t buf_E_01[50] = {0};
		uint8_t buf_T_01[4] = {0};
		uint8_t buf_F_01[2] = {0};

		flo_to_str_V(Voltage_01, buf_V_01, 1);
		flo_to_str(Current_01, buf_C_01, 3);
		flo_to_str(Active_power_01/1000, buf_A_01, 4);
		flo_to_str(Electricity_Quantity_01, buf_E_01, 2);
		sprintf(buf_T_01, "%d", Temperature_01);
		sprintf(buf_F_01, "%02d", Fault_type_01);

		uint8_t buf_V_02[50] = {0};
		uint8_t buf_C_02[50] = {0};
		uint8_t buf_A_02[50] = {0};
		uint8_t buf_E_02[50] = {0};
		uint8_t buf_T_02[4] = {0};
		uint8_t buf_F_02[2] = {0};

		flo_to_str_V(Voltage_02, buf_V_02, 1);
		flo_to_str(Current_02, buf_C_02, 3);
		flo_to_str(Active_power_02/1000, buf_A_02, 4);
		flo_to_str(Electricity_Quantity_02, buf_E_02, 2);
		sprintf(buf_T_02, "%d", Temperature_02);
		sprintf(buf_F_02, "%02d", Fault_type_02);


		uint8_t buf_V_03[50] = {0};
		uint8_t buf_C_03[50] = {0};
		uint8_t buf_A_03[50] = {0};
		uint8_t buf_E_03[50] = {0};
		uint8_t buf_T_03[4] = {0};
		uint8_t buf_F_03[2] = {0};

		flo_to_str_V(Voltage_03, buf_V_03, 1);
		flo_to_str(Current_03, buf_C_03, 3);
		flo_to_str(Active_power_03, buf_A_03, 4);
		flo_to_str(Electricity_Quantity_03, buf_E_03, 2);
		sprintf(buf_T_03, "%d", Temperature_03);
		sprintf(buf_F_03, "%02d", Fault_type_03);

		strcat(rs_buf, "#rs#");
		strcat(rs_buf, buffer);
		strcat(rs_buf, "03#01;");
		strcat(rs_buf, buf_V_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F_01);

		strcat(rs_buf, "#02;");
		strcat(rs_buf, buf_V_02);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C_02);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A_02);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E_02);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T_02);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F_02);

		strcat(rs_buf, "#03;");
		strcat(rs_buf, buf_V_03);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C_03);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A_03);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E_03);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T_03);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F_03);

		strcat(rs_buf, "#");
		rs_buf[strlen(rs_buf)] = '\0';
		printf("rs_buf:%s\n", rs_buf);
		break;}
	
	case 4: {
		uint8_t buf_V_01[50] = {0};
		uint8_t buf_C_01[50] = {0};
		uint8_t buf_A_01[50] = {0};
		uint8_t buf_E_01[50] = {0};
		uint8_t buf_T_01[4] = {0};
		uint8_t buf_F_01[2] = {0};

		flo_to_str_V(Voltage_01, buf_V_01, 1);
		flo_to_str(Current_01, buf_C_01, 3);
		flo_to_str(Active_power_01/1000, buf_A_01, 4);
		flo_to_str(Electricity_Quantity_01, buf_E_01, 2);
		sprintf(buf_T_01, "%d", Temperature_01);
		sprintf(buf_F_01, "%02d", Fault_type_01);

		uint8_t buf_V_02[50] = {0};
		uint8_t buf_C_02[50] = {0};
		uint8_t buf_A_02[50] = {0};
		uint8_t buf_E_02[50] = {0};
		uint8_t buf_T_02[4] = {0};
		uint8_t buf_F_02[2] = {0};

		flo_to_str_V(Voltage_02, buf_V_02, 1);
		flo_to_str(Current_02, buf_C_02, 3);
		flo_to_str(Active_power_02/1000, buf_A_02, 4);
		flo_to_str(Electricity_Quantity_02, buf_E_02, 2);
		sprintf(buf_T_02, "%d", Temperature_02);
		sprintf(buf_F_02, "%02d", Fault_type_02);


		uint8_t buf_V_03[50] = {0};
		uint8_t buf_C_03[50] = {0};
		uint8_t buf_A_03[50] = {0};
		uint8_t buf_E_03[50] = {0};
		uint8_t buf_T_03[4] = {0};
		uint8_t buf_F_03[2] = {0};

		flo_to_str_V(Voltage_03, buf_V_03, 1);
		flo_to_str(Current_03, buf_C_03, 3);
		flo_to_str(Active_power_03/1000, buf_A_03, 4);
		flo_to_str(Electricity_Quantity_03, buf_E_03, 2);
		sprintf(buf_T_03, "%d", Temperature_03);
		sprintf(buf_F_03, "%02d", Fault_type_03);


		uint8_t buf_V_04[50] = {0};
		uint8_t buf_C_04[50] = {0};
		uint8_t buf_A_04[50] = {0};
		uint8_t buf_E_04[50] = {0};
		uint8_t buf_T_04[4] = {0};
		uint8_t buf_F_04[2] = {0};

		flo_to_str_V(Voltage_04, buf_V_04, 1);
		flo_to_str(Current_04, buf_C_04, 3);
		flo_to_str(Active_power_04/1000, buf_A_04, 4);
		flo_to_str(Electricity_Quantity_04, buf_E_04, 2);
		sprintf(buf_T_04, "%d", Temperature_04);
		sprintf(buf_F_04, "%02d", Fault_type_04);

		strcat(rs_buf, "#rs#");
		strcat(rs_buf, buffer);
		strcat(rs_buf, "04#01;");
		strcat(rs_buf, buf_V_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F_01);

		strcat(rs_buf, "#02;");
		strcat(rs_buf, buf_V_02);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C_02);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A_02);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E_02);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T_02);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F_02);

		strcat(rs_buf, "#03;");
		strcat(rs_buf, buf_V_03);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C_03);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A_03);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E_03);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T_03);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F_03);

		strcat(rs_buf, "#04;");
		strcat(rs_buf, buf_V_04);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C_04);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A_04);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E_04);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T_04);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F_04);

		strcat(rs_buf, "#");
		rs_buf[strlen(rs_buf)] = '\0';
		printf("send_buf:%s\n", rs_buf);
		break;}
	
	case 5: {
		uint8_t buf_V_01[50] = {0};
		uint8_t buf_C_01[50] = {0};
		uint8_t buf_A_01[50] = {0};
		uint8_t buf_E_01[50] = {0};
		uint8_t buf_T_01[4] = {0};
		uint8_t buf_F_01[2] = {0};

		flo_to_str_V(Voltage_01, buf_V_01, 1);
		flo_to_str(Current_01, buf_C_01, 3);
		flo_to_str(Active_power_01/1000, buf_A_01, 4);
		flo_to_str(Electricity_Quantity_01, buf_E_01, 2);
		sprintf(buf_T_01, "%d", Temperature_01);
		sprintf(buf_F_01, "%02d", Fault_type_01);

		uint8_t buf_V_02[50] = {0};
		uint8_t buf_C_02[50] = {0};
		uint8_t buf_A_02[50] = {0};
		uint8_t buf_E_02[50] = {0};
		uint8_t buf_T_02[4] = {0};
		uint8_t buf_F_02[2] = {0};

		flo_to_str_V(Voltage_02, buf_V_02, 1);
		flo_to_str(Current_02, buf_C_02, 3);
		flo_to_str(Active_power_02/1000, buf_A_02, 4);
		flo_to_str(Electricity_Quantity_02, buf_E_02, 2);
		sprintf(buf_T_02, "%d", Temperature_02);
		sprintf(buf_F_02, "%02d", Fault_type_02);


		uint8_t buf_V_03[50] = {0};
		uint8_t buf_C_03[50] = {0};
		uint8_t buf_A_03[50] = {0};
		uint8_t buf_E_03[50] = {0};
		uint8_t buf_T_03[4] = {0};
		uint8_t buf_F_03[2] = {0};

		flo_to_str_V(Voltage_03, buf_V_03, 1);
		flo_to_str(Current_03, buf_C_03, 3);
		flo_to_str(Active_power_03/1000, buf_A_03, 4);
		flo_to_str(Electricity_Quantity_03, buf_E_03, 2);
		sprintf(buf_T_03, "%d", Temperature_03);
		sprintf(buf_F_03, "%02d", Fault_type_03);


		uint8_t buf_V_04[50] = {0};
		uint8_t buf_C_04[50] = {0};
		uint8_t buf_A_04[50] = {0};
		uint8_t buf_E_04[50] = {0};
		uint8_t buf_T_04[4] = {0};
		uint8_t buf_F_04[2] = {0};

		flo_to_str_V(Voltage_04, buf_V_04, 1);
		flo_to_str(Current_04, buf_C_04, 3);
		flo_to_str(Active_power_04/1000, buf_A_04, 4);
		flo_to_str(Electricity_Quantity_04, buf_E_04, 2);
		sprintf(buf_T_04, "%d", Temperature_04);
		sprintf(buf_F_04, "%02d", Fault_type_04);


		uint8_t buf_V_05[50] = {0};
		uint8_t buf_C_05[50] = {0};
		uint8_t buf_A_05[50] = {0};
		uint8_t buf_E_05[50] = {0};
		uint8_t buf_T_05[4] = {0};
		uint8_t buf_F_05[2] = {0};

		flo_to_str_V(Voltage_05, buf_V_05, 1);
		flo_to_str(Current_05, buf_C_05, 3);
		flo_to_str(Active_power_05/1000, buf_A_05, 4);
		flo_to_str(Electricity_Quantity_05, buf_E_05, 2);
		sprintf(buf_T_05, "%d", Temperature_05);
		sprintf(buf_F_05, "%02d", Fault_type_05);

		strcat(rs_buf, "#rs#");
		strcat(rs_buf, buffer);
		strcat(rs_buf, "05#01;");
		strcat(rs_buf, buf_V_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F_01);

		strcat(rs_buf, "#02;");
		strcat(rs_buf, buf_V_02);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C_02);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A_02);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E_02);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T_02);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F_02);

		strcat(rs_buf, "#03;");
		strcat(rs_buf, buf_V_03);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C_03);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A_03);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E_03);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T_03);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F_03);

		strcat(rs_buf, "#04;");
		strcat(rs_buf, buf_V_04);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C_04);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A_04);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E_04);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T_04);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F_04);

		strcat(rs_buf, "#05;");
		strcat(rs_buf, buf_V_05);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C_05);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A_05);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E_05);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T_05);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F_05);

		strcat(rs_buf, "#");
		rs_buf[strlen(rs_buf)] = '\0';
		printf("rs_buf:%s\n", rs_buf);
		break;
	}
	
	case 6: {
		uint8_t buf_V_01[50] = {0};
		uint8_t buf_C_01[50] = {0};
		uint8_t buf_A_01[50] = {0};
		uint8_t buf_E_01[50] = {0};
		uint8_t buf_T_01[4] = {0};
		uint8_t buf_F_01[2] = {0};

		flo_to_str_V(Voltage_01, buf_V_01, 1);
		flo_to_str(Current_01, buf_C_01, 3);
		flo_to_str(Active_power_01/1000, buf_A_01, 4);
		flo_to_str(Electricity_Quantity_01, buf_E_01, 2);
		sprintf(buf_T_01, "%d", Temperature_01);
		sprintf(buf_F_01, "%02d", Fault_type_01);

		uint8_t buf_V_02[50] = {0};
		uint8_t buf_C_02[50] = {0};
		uint8_t buf_A_02[50] = {0};
		uint8_t buf_E_02[50] = {0};
		uint8_t buf_T_02[4] = {0};
		uint8_t buf_F_02[2] = {0};

		flo_to_str_V(Voltage_02, buf_V_02, 1);
		flo_to_str(Current_02, buf_C_02, 3);
		flo_to_str(Active_power_02/1000, buf_A_02, 4);
		flo_to_str(Electricity_Quantity_02, buf_E_02, 2);
		sprintf(buf_T_02, "%d", Temperature_02);
		sprintf(buf_F_02, "%02d", Fault_type_02);


		uint8_t buf_V_03[50] = {0};
		uint8_t buf_C_03[50] = {0};
		uint8_t buf_A_03[50] = {0};
		uint8_t buf_E_03[50] = {0};
		uint8_t buf_T_03[4] = {0};
		uint8_t buf_F_03[2] = {0};

		flo_to_str_V(Voltage_03, buf_V_03, 1);
		flo_to_str(Current_03, buf_C_03, 3);
		flo_to_str(Active_power_03/1000, buf_A_03, 4);
		flo_to_str(Electricity_Quantity_03, buf_E_03, 2);
		sprintf(buf_T_03, "%d", Temperature_03);
		sprintf(buf_F_03, "%02d", Fault_type_03);


		uint8_t buf_V_04[50] = {0};
		uint8_t buf_C_04[50] = {0};
		uint8_t buf_A_04[50] = {0};
		uint8_t buf_E_04[50] = {0};
		uint8_t buf_T_04[4] = {0};
		uint8_t buf_F_04[2] = {0};

		flo_to_str_V(Voltage_04, buf_V_04, 1);
		flo_to_str(Current_04, buf_C_04, 3);
		flo_to_str(Active_power_04/1000, buf_A_04, 4);
		flo_to_str(Electricity_Quantity_04, buf_E_04, 2);
		sprintf(buf_T_04, "%d", Temperature_04);
		sprintf(buf_F_04, "%02d", Fault_type_04);


		uint8_t buf_V_05[50] = {0};
		uint8_t buf_C_05[50] = {0};
		uint8_t buf_A_05[50] = {0};
		uint8_t buf_E_05[50] = {0};
		uint8_t buf_T_05[4] = {0};
		uint8_t buf_F_05[2] = {0};

		flo_to_str_V(Voltage_05, buf_V_05, 1);
		flo_to_str(Current_05, buf_C_05, 3);
		flo_to_str(Active_power_05/1000, buf_A_05, 4);
		flo_to_str(Electricity_Quantity_05, buf_E_05, 2);
		sprintf(buf_T_05, "%d", Temperature_05);
		sprintf(buf_F_05, "%02d", Fault_type_05);


		uint8_t buf_V_06[50] = {0};
		uint8_t buf_C_06[50] = {0};
		uint8_t buf_A_06[50] = {0};
		uint8_t buf_E_06[50] = {0};
		uint8_t buf_T_06[4] = {0};
		uint8_t buf_F_06[2] = {0};

		flo_to_str_V(Voltage_06, buf_V_06, 1);
		flo_to_str(Current_06, buf_C_06, 3);
		flo_to_str(Active_power_06/1000, buf_A_06, 4);
		flo_to_str(Electricity_Quantity_06, buf_E_06, 2);
		sprintf(buf_T_06, "%d", Temperature_06);
		sprintf(buf_F_06, "%02d", Fault_type_06);

		strcat(rs_buf, "#rs#");
		strcat(rs_buf, buffer);
		strcat(rs_buf, "06#01;");
		strcat(rs_buf, buf_V_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T_01);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F_01);

		strcat(rs_buf, "#02;");
		strcat(rs_buf, buf_V_02);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C_02);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A_02);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E_02);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T_02);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F_02);

		strcat(rs_buf, "#03;");
		strcat(rs_buf, buf_V_03);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C_03);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A_03);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E_03);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T_03);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F_03);

		strcat(rs_buf, "#04;");
		strcat(rs_buf, buf_V_04);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C_04);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A_04);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E_04);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T_04);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F_04);

		strcat(rs_buf, "#05;");
		strcat(rs_buf, buf_V_05);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C_05);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A_05);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E_05);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T_05);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F_05);

		strcat(rs_buf, "#06;");
		strcat(rs_buf, buf_V_06);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_C_06);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_A_06);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_E_06);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_T_06);
		strcat(rs_buf, ";");
		strcat(rs_buf, buf_F_06);

		strcat(rs_buf, "#");
		rs_buf[strlen(rs_buf)] = '\0';
		printf("rs_buf:%s\n", rs_buf);
		break;
	}
	default:
		break;
	}
}

void Read_One_Device(uint8_t *buffer, uint8_t* rs_buf) {  	//"0029"
	uint8_t serial_number[4] = {0};
	uint8_t Fault_type_buf[4] = {0};
	uint8_t encryption_buff[N] = {0};

	memcpy(serial_number, buffer+45, 2);
	serial_number[strlen(serial_number)] = '\0';

	switch (getnum(serial_number)) {
	case 1:
		sprintf(Fault_type_buf, "%02d", Fault_type_01);
		strcat(rs_buf, "#rs#");
		strcat(rs_buf, buffer);
		strcat(rs_buf, Fault_type_buf);
		strcat(rs_buf, "#");
		
		rs_buf[strlen(rs_buf)] = '\0';
		printf("rs_buf:%s\n", rs_buf);
		break;
		
	case 2:
		sprintf(Fault_type_buf, "%02d", Fault_type_02);
		strcat(rs_buf, "#rs#");
		strcat(rs_buf, buffer);
		strcat(rs_buf, Fault_type_buf);
		strcat(rs_buf, "#");
		
		rs_buf[strlen(rs_buf)] = '\0';
		printf("rs_buf:%s\n", rs_buf);
		break;
		
	case 3:
		sprintf(Fault_type_buf, "%02d", Fault_type_03);
		strcat(rs_buf, "#rs#");
		strcat(rs_buf, buffer);
		strcat(rs_buf, Fault_type_buf);
		strcat(rs_buf, "#");
		
		rs_buf[strlen(rs_buf)] = '\0';
		printf("rs_buf:%s\n", rs_buf);
		break;
		
	case 4:
		sprintf(Fault_type_buf, "%02d", Fault_type_04);
		strcat(rs_buf, "#rs#");
		strcat(rs_buf, buffer);
		strcat(rs_buf, Fault_type_buf);
		strcat(rs_buf, "#");
		
		rs_buf[strlen(rs_buf)] = '\0';
		printf("rs_buf:%s\n", rs_buf);

		break;
	case 5:
		sprintf(Fault_type_buf, "%02d", Fault_type_05);
		strcat(rs_buf, "#rs#");
		strcat(rs_buf, buffer);
		strcat(rs_buf, Fault_type_buf);
		strcat(rs_buf, "#");
		
		rs_buf[strlen(rs_buf)] = '\0';
		printf("rs_buf:%s\n", rs_buf);
		break;
		
	case 6:
		sprintf(Fault_type_buf, "%02d", Fault_type_06);
		strcat(rs_buf, "#rs#");
		strcat(rs_buf, buffer);
		strcat(rs_buf, Fault_type_buf);
		strcat(rs_buf, "#");
		
		rs_buf[strlen(rs_buf)] = '\0';
		printf("rs_buf:%s\n", rs_buf);
		break;
		
	default:
		break;
	}
}
void  Heartbeat_Package(uint8_t *buffer) {
	printf("------------- Heartbeat Package Asked Succeed!!-------------\n\n");
}




