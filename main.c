#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(){
	
	char ipv4[15];
	char mask[15];

	int lastbit = 128;
	
	printf("IP address\n>_");
	scanf("%s",ipv4);
	
	printf("Subnet Mask or CIDR prefix (*** in /.. format ***)\n>_");
	scanf("%s",mask);
	
	int ip[4];
	char *token = strtok(ipv4,".");
	int i=0;
	while(token != NULL){
		ip[i++]=atoi(token);
		token=strtok(NULL,".");
	}

	int CIDR=0;
	int subnet[4];

	if(mask[0]=='/'){
		CIDR = atoi(mask+1);
		for(int i=0;i<4;i++){
			int temp=0;
			if(CIDR==0){
				subnet[i]=0;
			}
			if(CIDR<8){
				for(int j=0;j<CIDR;j++){
					temp+=0|lastbit;
					lastbit>>=1;
				}
				CIDR=0;
				lastbit=128;
				subnet[i]=temp;
			}
			if(CIDR>=8){
				CIDR-=8;
				subnet[i]=255;
			}
			
		}
	}
	else{
		token = strtok(mask,".");
		i=0;
		while(token != NULL){
			subnet[i++]=atoi(token);
			token=strtok(NULL,".");
		}
	}

	for (int i = 0; i < 4; ++i){
			while(lastbit!=0){
			if(lastbit&subnet[i]){
				CIDR++;
				lastbit>>=1;
			}
			else
				break;
		}
		lastbit=128;
	}
	//printf("%d\n",CIDR );

	int network[4];
	for (int i = 0; i < 4; ++i){
		network[i]=ip[i]&subnet[i];
	}
	
	int power(int x, int y){
		int result = 1;
		for(int i=0;i<y;i++)
			result*=x;
		return result;
	}

	void printip(int *ip){
		printf("%d.%d.%d.%d",ip[0] ,ip[1] ,ip[2] ,ip[3]);
	}

	int *broadcastip(int hosts, int *network){
		int *broadcast = (int*)malloc(sizeof(int)*4);
		for (int i = 0; i < 4; ++i)
		{
			broadcast[i]=network[i];
		}
		while(hosts!=0){
			if(broadcast[3]>255){
				broadcast[2]+=1;
				broadcast[3]-=256;
			}
			if(broadcast[2]>255){
				broadcast[1]+=1;
				broadcast[2]-=256;
			}
			if(broadcast[1]>255){
				broadcast[0]+=1;
				broadcast[1]-=256;
			}
			if(hosts<255){
				broadcast[3]+=hosts-1;
				hosts-=hosts;
			}
			else{
				broadcast[3]+=255;
				hosts-=255;
			}
			
		}
		return broadcast;
	}
	
	int hosts = power(2,32-CIDR);
	int *broadcast = (int *)malloc(sizeof(int)*4);
	broadcast = broadcastip(hosts,network);

	printf("Network Address: ");
	printip(network);

	printf("\nSubnet Mask: ");
	printip(subnet);

	printf("\nBroadcast Address: ");
	printip(broadcast);

	printf("\nIP Range: ");
	printip(network);
	printf(" - ");
	printip(broadcast);

	printf("\nNetwork prefix bits: %d\n",CIDR );

	printf("Host per network: %d\n",hosts - 2);

}
