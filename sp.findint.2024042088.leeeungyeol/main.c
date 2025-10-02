#include <stdio.h> //표준 입출력
#include <math.h> //절대값 계산을 위한 헤더파일 
#include <sys/time.h> //실행시간을 측정하기 위한 헤더파일

void quick(double arr[], int low, int high) { //퀵소트 함수, low부터 high까지 정렬
	if (low >= high) return; //종료 조건 : 구간이 하나 이하이면 끝

	double pivot = arr[(low + high) / 2]; //피봇은 가운데 값으로 정하기
	int left = low; //왼쪽 시작위치
	int right = high; //오른쪽 시작위치

	while (left <= right) { //왼쪽이 오른쪽보다 작을 때만 반복
		while (arr[left] < pivot) left++; //피봇보다 작은 값을 찾을 떄까지 증가시키기
		while (arr[right] > pivot) right--; //피봇보다 큰 값을 찾을 떄까지 감소

		if (left <= right) { //left가 right보다 작거나 같다면 
			double temp = arr[left]; //두 값을 교환하기 위한 임시저장소
			arr[left] = arr[right]; //두 값을
			arr[right] = temp; //교환해주기
			left++; //left를 증가시켜서 다음값보기
			right--; //right를 감소시켜서 다음값보기
		}
	}

	quick(arr, low, right); //이제 피봇기준 왼쪽 정렬
	quick(arr, left, high); //오른쪽 정렬해주기
}


int main() {
	struct timeval start, end; //시간 측정용 구조체
	gettimeofday(&start, NULL); //프로그램 시작 시점 여기서부터 시간을 잴것

	double num[100000]; //10만개 데이터를 저장할 배열
	FILE* fp; //파일 입출력을 위한 파일포인터
	fp = fopen("input.txt", "r"); //파일 열어주기

	int i; //for문을 위한 변수 i
	for (i = 0; i < 100000; i++) { //10만개의 데이터를 읽을 for문
		fscanf(fp, "%lf", &num[i]); //10만개의 데이터 읽어서 배열에 저장하기
	}
	fclose(fp); //파일 닫아주기

	quick(num, 0, 99999); //퀵정렬 해주기

	int uni = 1; //0번째 자료는 유니크하니까 1로 초기화하기
	int j; //for문을 위한 변수 j
	for (j = 1; j < 100000;j++) { //배열을 돌면서 인접한 두 수의 차이의 절대값이 1e-9보다 크면 서로 다른 값으로 보고
		if (fabs(num[j] - num[j - 1]) > 1e-9) { //1e-9 : 10의 -9제곱
			uni++; //증가시켜주기
		}
	}

	int over = 0; //5000을 넘는 수를 세주기 위한 변수
	int k; //for문을 위한 변수 k
	for (k = 0; k < 100000; k++) { //만번 돌아주면서
		if (num[k] > 5000.0) { //값이 5000.0보다 크다면 
			over++; //세어주기
		}
	}

	gettimeofday(&end, NULL); //시간 측정 멈추기

	printf("The number of unique values: %d\n", uni); //유니크한 수 출력
	printf("The number of more than 5000 values: %d\n", over); //5000을 넘는 수 출력
	double extime = (end.tv_sec - start.tv_sec) + //끝난 시간 - 시작한 시간을 저장해서
		(end.tv_usec - start.tv_usec) / 1000000.0; //마이크로초 단위로 변환하기

	printf("Execution time: %.6f sec", extime); //측정된 시간 출력해주기

	return 0; //main 함수 끝
}

