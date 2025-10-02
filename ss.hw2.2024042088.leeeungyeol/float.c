#include <stdio.h> //ǥ�� ������� ���� ���� 
#include <string.h> //���ڿ� �Լ� strlen �� ���� ���ֱ� 


float change(char *bit) { //�Ǽ��� ��ȯ���ִ� �Լ� 
    int sign = (bit[0] == '0') ? 1 : -1; //0�̸� ���, 1�̸� ������ ��ȣ ������ֱ� 

    int e = 0; //������ ���� �������� ���� 
    int i;//for���� ���� ���� 
    for(i = 1; i <= 8; i++) { //1������ 8�������� ������
        e = (e << 1) | (bit[i]-'0'); //���� ���� e�� �������� 1��Ʈ �̵� �ؼ� ���� 2�谡 ��, ���ڸ� ������ �ٲ��ְ� | �������� ���� ��Ʈ�� e�� �ֱ�
		 
    }

    float f = 0.0f; //������ ����� ���� ���� 
    float fac = 0.5f; //���� ��� ���۰� 2�� -1���̴ϱ� 0.5 
    for(i = 9; i < 32; i++){ //9���� 32�� �ε����� ������ 
        if(bit[i] == '1') f += fac; //��Ʈ�� 1�̸� ������ fac �����ֱ� 
        fac /= 2.0f; //���� ��Ʈ�� 2�� ���� �� 
    }

    float exp_val = 1.0f; //���� ��� ��� ����� 
    int exp = e - 127; //32��Ʈ�ϱ� 127 ���ֱ� 
    if(exp > 0) { //������ ����϶�  
        for(i=0;i<exp;i++){ //exp��ŭ 2�� �����ֱ� 
            exp_val*=2.0f; //2^i ���ϱ� 
        } 
    }
    else if(exp<0) { //������ ������ ��� 
        for(i=0;i<-exp;i++){ //exp��ŭ 2 ������ 
            exp_val/=2.0f; //2^i ������ 
        } 
    }
    
    return sign*(1.0f+f)*exp_val; //���� : ��ȣ * (1+����) * 2^���� 
}

void print_float(FILE *fp, float f){ //������� ������ �Լ���
 
    char buf[64]; //�ӽ� ���ڿ��� ������ ���� 
    sprintf(buf,"%.9f",f); //�Ҽ��� �Ʒ� 9�ڸ����� ��ȯ���ֱ� 
    int len = strlen(buf); //���ڿ� ���� ������ֱ� 
    while(len>0 && buf[len-1]=='0') len--; //�ʿ���� 0 �������ֱ� 
    if(len>0 && buf[len-1]=='.') len--; //�Ҽ����� ������ �������ֱ� 
    buf[len]='\0'; //���ڿ� ���� �ι��� �־��ֱ� 
    fprintf(fp,"%s\n",buf); //���Ͽ� ���ֱ� 
}

int main(int argc, char *argv[]){ //argument ���� ó���� 
    FILE *fp = fopen(argv[1],"r"); //�Է� ���� �����ֱ� 
    FILE *fp2 = fopen("output.txt", "w"); //������� �����ֱ� 

    char patterns[1002][33]; //��Ʈ������ �������� 2���� �迭 
    int cnt = 0; //���� �Էµ� ���ڿ��� ���� 

    while(fscanf(fp,"%32s",patterns[cnt])==1) cnt++; //�Է� ���Ͽ��� 32��Ʈ ���ڿ� �о ���� �迭�� �ְ� cnt���� 

    int i;//for���� ���� i 
    for(i=0;i<cnt;i++){ //cnt ��ŭ  
        float f = change(patterns[i]); //��ȯ���ְ� 
        print_float(fp2,f); //������ֱ� 
    }

    fclose(fp); //�Է� ���� �ݾ��ֱ� 
    fclose(fp2); //��� ���� �ݾ��ֱ� 
    return 0; //�� 
}


