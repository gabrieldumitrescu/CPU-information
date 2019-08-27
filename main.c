#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct FrequencyInfoT
{
	short base,max,bus;
} FrequencyInfo;


typedef struct FeatureInfoT
{
	unsigned int part1,part2;
	unsigned int familyModelStepping;
	unsigned ProcCNT;
} FeatureInfo;

typedef enum FeatureNameT
{SSE3=0,PCLMULQDQ,DTES64,MONITOR,DS_CPL,VMX,SMX,EIST,TM2,
SSSE3,CNXT_ID,SDBG,FMA,CMPXCHG16B,XTPR_UPDATE_CONTROL,PDCM,
RESERVED,PCID,DCA,SSE4_1,SSE4_2,X2APIC,MOVBE,POPCNT,
TSC_DEADLINE,AESNI,XSAVE,OSXSAVE,AVX,F16C,RDRAND,NOTUSED,
FPU,VME,DE,PSE,TSC,MSR,PAE,MCE,CX8,APIC,RESERVED2,SEP,MTRR,
PGE,MCA,CMOV,PAT,PSE_36,PSN,CLFLSH,RESERVED3,DS,ACPI,MMX,
FXSR,SSE,SSE2,SS,HTT,TM,RESERVED4,PBE
} FeatureName;

/* Assembly functions */
int vendorID(char*);
int brandString(char*);
void getFrequencyInfo(FrequencyInfo*);
void getFeatureInfo(FeatureInfo*);
/* End Assembly functions */


void printFamilyModelStepping(unsigned EaxValue)
{
	unsigned SteppingMask = 0xf;
	unsigned BaseModelMask = 0xf0;
	unsigned BaseFamilyMask = 0xf00;
	unsigned ExtModelMask = 0xf0000;
	unsigned ExtFamilyMask = 0xf00000;
	unsigned Stepping=EaxValue & SteppingMask;
	unsigned BaseModel=(EaxValue & BaseModelMask) >> 4;
	unsigned BaseFamily=(EaxValue & BaseFamilyMask) >> 8;
	unsigned ExtModel=((EaxValue & ExtModelMask) >> 12) | BaseModel;
	unsigned ExtFamily=((EaxValue & ExtFamilyMask) >> 20) + BaseFamily;
	printf("Processor stepping: %Xh\n",Stepping);
	printf("Processor base model: %Xh\n",BaseModel);
	printf("Processor base family: %Xh\n",BaseFamily);
	printf("Processor model: %Xh\n",ExtModel);
	printf("Processor family: %Xh\n",ExtFamily);
}

int processorSupport(FeatureInfo* f, FeatureName n)
{
	int pos=(int) n;
	int part=f->part1;
	if(pos>31){
		part=f->part2;
		pos-=32;
	}
	return (part & (1 << pos)) > 0;
}

void printFeatureInfo(FeatureInfo* fInfo)
{
	printf("Processor supports HyperThreading: %s\n",
		processorSupport(fInfo,HTT) ? "YES" : "NO");

	printf("Processor contains an x87 FPU: %s\n",
		processorSupport(fInfo,FPU) ? "YES" : "NO");

	printf("Processor supports PAE: %s\n",
		processorSupport(fInfo,PAE) ? "YES" : "NO");


	printf("Processor supports RDTSC instr.: %s\n",
		processorSupport(fInfo,TSC) ? "YES" : "NO");

	printf("Processor has an integrated APIC: %s\n",
		processorSupport(fInfo,APIC) ? "YES" : "NO");

	printf("Processor supports MMX: %s\n",
		processorSupport(fInfo,MMX) ? "YES" : "NO");

	printf("Processor supports SSE: %s\n",
		processorSupport(fInfo,SSE) ? "YES" : "NO");


	printf("Processor supports SSE2: %s\n",
		processorSupport(fInfo,SSE2) ? "YES" : "NO");

	printf("Processor supports SSE3: %s\n",
		processorSupport(fInfo,SSE3) ? "YES" : "NO");

	printf("Processor supports VMX: %s\n",
		processorSupport(fInfo,VMX) ? "YES" : "NO");

	printf("Processor supports EIST: %s\n",
		processorSupport(fInfo,EIST) ? "YES" : "NO");

	printf("Processor supports TM2: %s\n",
		processorSupport(fInfo,TM2) ? "YES" : "NO");

	printf("Processor supports Suplemental SSE3: %s\n",
		processorSupport(fInfo,SSSE3) ? "YES" : "NO");

	printf("Processor supports SSE4.1: %s\n",
		processorSupport(fInfo,SSE4_1) ? "YES" : "NO");

	printf("Processor supports SSE4.2: %s\n",
		processorSupport(fInfo,SSE4_2) ? "YES" : "NO");

	printf("Processor supports AVX: %s\n",
		processorSupport(fInfo,AVX) ? "YES" : "NO");

	printf("Processor supports CLFLUSH instruction: %s\n",
		processorSupport(fInfo,CLFLSH) ? "YES" : "NO");
}

int main(){
	char* str=(char*)malloc(16);
	int maxBasicValue=vendorID(str);
	printf("Maximum input value for basic CPUID info: 0x%X\n",maxBasicValue);
	printf("Processor vendor ID: %s\n",str);


	free(str);
	str=(char*)malloc(48);
	int OK=brandString(str);
	if(OK){
		printf("Processor brand string: \"%s\"\n",str);
		printf("Brand string length=%x\n",(unsigned)strlen(str));
	}
	else{
		printf("Error getting brand string!!!\n");
	}

	FeatureInfo fInfo;
	getFeatureInfo(&fInfo);
  printFamilyModelStepping(fInfo.familyModelStepping);
  printFeatureInfo(&fInfo);

	if(maxBasicValue>=0x16)
	{
		FrequencyInfo info;
		getFrequencyInfo(&info);
		printf("Processor frequency information:\n");
		printf("\t Base: %hu\n",info.base);
		printf("\t Maximum: %hu\n",info.max);
		printf("\t Bus: %hu\n",info.bus);
	}



	free(str);

	return 0;
}
