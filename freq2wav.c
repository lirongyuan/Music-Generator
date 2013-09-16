#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SampleRate 44100.0
#define NumChannels 1
#define BitsPerSample 16
#define ByteRate SampleRate*NumChannels*(BitsPerSample/8)
typedef struct WaveHeader {
	unsigned char chunkID[4];      // big endian 
	unsigned char chunkSize[4];    // little endian
	unsigned char format[4];       // big endian
	unsigned char subchunk1ID[4];  // big endian
	unsigned char subchunk1Size[4];// little endian
	unsigned char audioFormat[2]; // little endian
	unsigned char numChannels[2];  // little endian
	unsigned char sampleRate[4];   // little endian 
	unsigned char byteRate[4];     // little endian
	unsigned char blockAlign[2];   // little endian
	unsigned char bitsPerSample[2];// little endian
	unsigned char subchunk2ID[4];  // big endian
	unsigned char subchunk2Size[4];// little endian
	unsigned char data[1];         // little endian
}WaveHeader;

void assignLittleEndian4(unsigned char * dest, unsigned int value) {
	dest[0] = value & 0xFF;
	dest[1] = (value >> 8) & 0xFF;
	dest[2] = (value >> 16) & 0xFF;
	dest[3] = (value >> 24) & 0xFF;
}

int main(int argc, char ** argv)
{
	short value;
	unsigned int subchunk2Size,numSamples,dataSize,fileSize;
	int i,j,m,num,test,littleEndian,freq,msecs,totalmsecs,datas[100][2];
	char wavename[50],freqname[50];
	
        /******FILE OPERATIONS START******/
	if (argc <2) {
                printf("freq2wav freq-file\n");  
		exit(1);
        }
	for(i=0;((argv[1][i]!='\0')&&((wavename[i]=argv[1][i])!='.'));i++);
	wavename[i+1]='\0';
	sprintf(freqname,"%s%s",wavename,"freq");
	if(((argv[1][i])=='\0')||strcmp(argv[1],freqname)!=0){
		printf("Expected .freq file.\n");  exit(1);	
	}
	sprintf(wavename,"%s%s",wavename,"wav");
	printf("freqFile: %s\n",argv[1]);
	printf("waveFile: %s\n",wavename);
	FILE *infile=fopen(freqname,"r");
	if (infile==NULL){
			printf("File \"%s\" not found\n",argv[1]);  exit(1);
	}
	FILE *outfile= fopen(wavename, "w+");
	if (outfile==NULL){
			printf("File \"%s\" not found\n",argv[1]);  exit(1);
	}
	/******FILE OPERATIONS END******/
	/******GET INPUT START******/
	printf("Frequency file: (Hz,ms)");
	for(num=0,totalmsecs=0,numSamples=0;fscanf(infile,"%d %d",&freq,&msecs)==2;num++){
		if(num%10==0)
			printf("\n%d: ",num);
		printf("(%d,%d) ",freq,msecs);
		datas[num][0]=freq;
		datas[num][1]=msecs;
		numSamples=numSamples+msecs*(SampleRate/1000.0);		
		totalmsecs=totalmsecs+msecs;
	}
	printf("\n");
	/******GET INPUT END******/
	/******CREATE HEADER START******/
	subchunk2Size=numSamples*NumChannels*(BitsPerSample/8);
	dataSize= numSamples*NumChannels*(BitsPerSample/8);
	fileSize= sizeof(WaveHeader)-1+dataSize; 
	
	WaveHeader *whdr=(WaveHeader *)malloc(fileSize);
	whdr->chunkID[0]='R'; whdr->chunkID[1]='I'; whdr->chunkID[2]='F'; whdr->chunkID[3]='F';
	assignLittleEndian4(whdr->chunkSize,36);
	whdr->format[0] = 'W'; whdr->format[1] = 'A'; whdr->format[2] = 'V'; whdr->format[3] = 'E';
	whdr->subchunk1ID[0]='f'; whdr->subchunk1ID[1]='m'; 
	whdr->subchunk1ID[2]='t'; whdr->subchunk1ID[3]=' ';
	assignLittleEndian4(whdr->subchunk1Size,16);
	whdr->audioFormat[0]=1;  whdr->audioFormat[1]=0;
	whdr->numChannels[0]=NumChannels;  whdr->numChannels[1]=0;
	assignLittleEndian4(whdr->sampleRate,SampleRate);
	assignLittleEndian4(whdr->byteRate,ByteRate);
	whdr->blockAlign[0]=NumChannels * BitsPerSample/8;  whdr->blockAlign[1]=0;
	whdr->bitsPerSample[0] = BitsPerSample; whdr->bitsPerSample[1]=0;
	whdr->subchunk2ID[0]='d'; whdr->subchunk2ID[1]='a'; 
	whdr->subchunk2ID[2]='t'; whdr->subchunk2ID[3]='a';
	assignLittleEndian4(whdr->subchunk2Size,subchunk2Size);
	/******CREATE HEADER END******/
	/******TEST LITTLE ENDIAN START******/
	test=2;
	if(*((char *)&test)==2)
		littleEndian=1;
	else
		littleEndian=0;
	/******TEST LITTLE ENDIAN END******/
	/******ASSIGN DATA START******/
		for(i=0,m=0;i<num;i++){
			freq=datas[i][0];
			numSamples=datas[i][1]*(SampleRate/1000);
			for(j=0;j<numSamples;j++,m++){
				value=32767*sin(3.1415*freq*j/(SampleRate));
				if(littleEndian){
					whdr->data[2*m] = *((unsigned char *)&value);
					whdr->data[2*m+1] = *((unsigned char *)&value + 1);
				}else{
					whdr->data[2*m] = *((unsigned char *)&value + 1);
					whdr->data[2*m+1] = *((unsigned char *)&value);
				}
			}
		}
		
	/******ASSIGN DATA END******/
	/******WRITE FILE START******/
	fwrite(whdr, fileSize, 1, outfile);
	free(whdr);
	fclose(infile);
	fclose(outfile);
	/******WRITE FILE END******/
}
