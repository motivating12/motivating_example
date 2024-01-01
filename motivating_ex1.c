#include <stdio.h>
#include <string.h>
void sink_mtd(char *cmd);
void dummy();

char sensitive_data[20];

char *copy(char *dest, const char* src){
	return strcpy(dest, src);
}

void pass(){
	sink_mtd("Pass");
}
void fail(){
	sink_mtd("Fail");
}
void sink_mtd(char *cmd){
    printf("%s: %s\n",cmd, sensitive_data);//SLIVER_SINK
	char dest[50];
	memcpy(dest,sizeof(sensitive_data),sensitive_data);
}

void op(char *(str_op)(char *, const char *), const char *data){
	(*str_op)(sensitive_data, data); 
}

int auth(const char *buf){
	if( !strcmp(buf, "passwd") ){
		char data[100];
		fgets(data,sizeof(data),stdin);
		op(copy, data); //SLIVER_SOURCE
		return 1;
	}
	return 0;
}
void dummy(){
	printf("dummy\n");
}
void main(int argc, char **argv){
	int auth_ret=auth(argv[1]);
	if (auth_ret){
		dummy();
		pass();
	} else {
		fail();
	}
}
