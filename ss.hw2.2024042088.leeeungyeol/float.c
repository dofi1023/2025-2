#include <stdio.h> //표준 입출력을 위해 쓰기 
#include <string.h> //문자열 함수 strlen 응 위해 써주기 


float change(char *bit) { //실수로 변환해주는 함수 
    int sign = (bit[0] == '0') ? 1 : -1; //0이면 양수, 1이면 음수로 부호 계산해주기 

    int e = 0; //지수부 값을 저장해줄 변수 
    int i;//for문을 위한 변수 
    for(i = 1; i <= 8; i++) { //1번부터 8번까지는 지수부
        e = (e << 1) | (bit[i]-'0'); //기존 지수 e를 왼쪽으로 1비트 이동 해서 값이 2배가 됨, 문자를 정수로 바꿔주고 | 연산으로 현재 비트를 e에 넣기
		 
    }

    float f = 0.0f; //가수부 계산을 위한 변수 
    float fac = 0.5f; //가수 계산 시작값 2의 -1승이니까 0.5 
    for(i = 9; i < 32; i++){ //9부터 32번 인덱스는 가수부 
        if(bit[i] == '1') f += fac; //비트가 1이면 가수에 fac 더해주기 
        fac /= 2.0f; //다음 비트는 2배 작은 값 
    }

    float exp_val = 1.0f; //지수 계산 결과 저장용 
    int exp = e - 127; //32비트니까 127 빼주기 
    if(exp > 0) { //지수가 양수일때  
        for(i=0;i<exp;i++){ //exp만큼 2를 곱해주기 
            exp_val*=2.0f; //2^i 곱하기 
        } 
    }
    else if(exp<0) { //지수가 음수일 경우 
        for(i=0;i<-exp;i++){ //exp만큼 2 나누기 
            exp_val/=2.0f; //2^i 나누기 
        } 
    }
    
    return sign*(1.0f+f)*exp_val; //최종 : 부호 * (1+가수) * 2^지수 
}

void print_float(FILE *fp, float f){ //최종출력 조절용 함수수
 
    char buf[64]; //임시 문자열을 저장할 버퍼 
    sprintf(buf,"%.9f",f); //소수점 아래 9자리까지 변환해주기 
    int len = strlen(buf); //문자열 길이 계산해주기 
    while(len>0 && buf[len-1]=='0') len--; //필요없는 0 제거해주기 
    if(len>0 && buf[len-1]=='.') len--; //소수점만 남으면 제거해주기 
    buf[len]='\0'; //문자열 끝에 널문자 넣어주기 
    fprintf(fp,"%s\n",buf); //파일에 써주기 
}

int main(int argc, char *argv[]){ //argument 인자 처리용 
    FILE *fp = fopen(argv[1],"r"); //입력 파일 열어주기 
    FILE *fp2 = fopen("output.txt", "w"); //출력파일 열어주기 

    char patterns[1002][33]; //비트패턴을 저장해줄 2차원 배열 
    int cnt = 0; //실제 입력된 문자열의 갯수 

    while(fscanf(fp,"%32s",patterns[cnt])==1) cnt++; //입력 파일에서 32비트 문자열 읽어서 패턴 배열에 넣고 cnt증가 

    int i;//for문을 위한 i 
    for(i=0;i<cnt;i++){ //cnt 만큼  
        float f = change(patterns[i]); //변환해주고 
        print_float(fp2,f); //출력해주기 
    }

    fclose(fp); //입력 파일 닫아주기 
    fclose(fp2); //출력 파일 닫아주기 
    return 0; //끝 
}


