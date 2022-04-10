#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
    printf("[----- [김기남]  [2022299002] -----]\n");
	QueueType *cQ = createQueue();
	element data;
	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ)
{
    /*현재 front값이 rear와 같을 경우 빈값임*/
    if (cQ->front == cQ->rear){
        printf("Queue is Empty\n");
        return 1;
    }
    else{
        return 0;
    }
}

int isFull(QueueType *cQ)
{
    /* 현재 rear값에서 +1 에서 MAX_QUEUE_SIZE를 나눈 나머지가
       front와 같을 경우 Queue가 모두 찬 상태임*/
    if ((cQ->rear + 1) % MAX_QUEUE_SIZE == cQ->front){
        printf("Queue is Full\n");
        return 1;
    }
    else{
        return 0;
    }
}


void enQueue(QueueType *cQ, element item)
{
    // 원형큐가 Full일 경우 새로운 값을 넣을 수 없음
    if (isFull(cQ) == 1){
        return ;
    }
    /* 최근에 넣어진 값의 위치에서 다음 index로 이동한 후
       해당 위치에 item값을 할당함
       (단, 한 바퀴를 돌았을 경우 Queue의 시작 주소값에 할당한다.*/
    else{
        cQ->rear = cQ->rear + 1;
        cQ->rear = cQ->rear % MAX_QUEUE_SIZE;
        cQ->queue[cQ->rear] = item;
    }
}

void deQueue(QueueType *cQ, element *item)
{
    // 원형큐가 비었을 경우, front값이 deQueue 될 수 없음.
    if (isEmpty(cQ) == 1){
        return ;
    }
    /* 현재 Queue의 index(front)에서 다음 index로 이동한 후
       해당 index의 값을 item에 할당함
       (단, 한 바퀴를 돌았을 경우, Queue의 시작 주소값을 할당받는다.*/
    else{;
        cQ->front = cQ->front + 1;
        cQ->front = cQ->front % MAX_QUEUE_SIZE;
        *item = cQ->queue[cQ->front];
    }
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}

