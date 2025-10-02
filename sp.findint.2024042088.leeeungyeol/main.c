#include <stdio.h> //ǥ�� �����
#include <math.h> //���밪 ����� ���� ������� 
#include <sys/time.h> //����ð��� �����ϱ� ���� �������

void quick(double arr[], int low, int high) { //����Ʈ �Լ�, low���� high���� ����
	if (low >= high) return; //���� ���� : ������ �ϳ� �����̸� ��

	double pivot = arr[(low + high) / 2]; //�Ǻ��� ��� ������ ���ϱ�
	int left = low; //���� ������ġ
	int right = high; //������ ������ġ

	while (left <= right) { //������ �����ʺ��� ���� ���� �ݺ�
		while (arr[left] < pivot) left++; //�Ǻ����� ���� ���� ã�� ������ ������Ű��
		while (arr[right] > pivot) right--; //�Ǻ����� ū ���� ã�� ������ ����

		if (left <= right) { //left�� right���� �۰ų� ���ٸ� 
			double temp = arr[left]; //�� ���� ��ȯ�ϱ� ���� �ӽ������
			arr[left] = arr[right]; //�� ����
			arr[right] = temp; //��ȯ���ֱ�
			left++; //left�� �������Ѽ� ����������
			right--; //right�� ���ҽ��Ѽ� ����������
		}
	}

	quick(arr, low, right); //���� �Ǻ����� ���� ����
	quick(arr, left, high); //������ �������ֱ�
}


int main() {
	struct timeval start, end; //�ð� ������ ����ü
	gettimeofday(&start, NULL); //���α׷� ���� ���� ���⼭���� �ð��� ���

	double num[100000]; //10���� �����͸� ������ �迭
	FILE* fp; //���� ������� ���� ����������
	fp = fopen("input.txt", "r"); //���� �����ֱ�

	int i; //for���� ���� ���� i
	for (i = 0; i < 100000; i++) { //10������ �����͸� ���� for��
		fscanf(fp, "%lf", &num[i]); //10������ ������ �о �迭�� �����ϱ�
	}
	fclose(fp); //���� �ݾ��ֱ�

	quick(num, 0, 99999); //������ ���ֱ�

	int uni = 1; //0��° �ڷ�� ����ũ�ϴϱ� 1�� �ʱ�ȭ�ϱ�
	int j; //for���� ���� ���� j
	for (j = 1; j < 100000;j++) { //�迭�� ���鼭 ������ �� ���� ������ ���밪�� 1e-9���� ũ�� ���� �ٸ� ������ ����
		if (fabs(num[j] - num[j - 1]) > 1e-9) { //1e-9 : 10�� -9����
			uni++; //���������ֱ�
		}
	}

	int over = 0; //5000�� �Ѵ� ���� ���ֱ� ���� ����
	int k; //for���� ���� ���� k
	for (k = 0; k < 100000; k++) { //���� �����ָ鼭
		if (num[k] > 5000.0) { //���� 5000.0���� ũ�ٸ� 
			over++; //�����ֱ�
		}
	}

	gettimeofday(&end, NULL); //�ð� ���� ���߱�

	printf("The number of unique values: %d\n", uni); //����ũ�� �� ���
	printf("The number of more than 5000 values: %d\n", over); //5000�� �Ѵ� �� ���
	double extime = (end.tv_sec - start.tv_sec) + //���� �ð� - ������ �ð��� �����ؼ�
		(end.tv_usec - start.tv_usec) / 1000000.0; //����ũ���� ������ ��ȯ�ϱ�

	printf("Execution time: %.6f sec", extime); //������ �ð� ������ֱ�

	return 0; //main �Լ� ��
}

