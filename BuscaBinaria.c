#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int main(int argc, char**argv){
	FILE *arquivo;
    Endereco endereco;
	int pos;
    long inicio, meio, fim, tamarq;

    if(argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}

    arquivo = fopen("cep_ordenado.dat","r");
    fseek(arquivo,0,SEEK_END);
    tamarq = ftell(arquivo);
    rewind(arquivo);

	inicio = 0;
    fim = (tamarq/sizeof(Endereco)) - 1;
	pos = 0;

    while(inicio <= fim){
        pos++;
        meio = (inicio+fim)/2;

		fseek(arquivo,meio * sizeof(Endereco),SEEK_SET);
		fread(&endereco,sizeof(Endereco),1,arquivo);
		
        if(strncmp(argv[1],endereco.cep,8)==0){
			printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",endereco.logradouro,endereco.bairro,endereco.cidade,endereco.uf,endereco.sigla,endereco.cep);
			break;
        }
		else if(strncmp(argv[1],endereco.cep,8)>0){
			inicio = meio + 1;
        }
		else{
			fim = meio - 1;
        }
    }
	printf("Total lido: %d\n", pos);
    fclose(arquivo);
	return 0;
}