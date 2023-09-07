#include<stdio.h>
#include<locale.h>
#include<stdlib.h>  
#include <string.h>
#include <time.h>
#define max_salas 5
#define max_filmes 5
#define max_sessoes 5
#define max_atores 5


struct Sala{
	int codigo, capacidade;
	char nome[40], tipo_exibicao[40];
	char acessivel;
};

struct Filme{
	int codigo, ano_lancamento;
	char nome[40], diretor[40];
	char atores[max_atores][40];
	int posicao_atores;
};

struct Sessao{
	int codigo_sala, codigo_filme;     
	float preco_ingresso;
	struct tm data_hora;
};


//fun��es Arquivos
void abre_arq_sala(struct Sala *vetor_sala, int *num_salas);
void abre_arq_filme(struct Filme *vetor_filme, int *num_filmes);
void abre_arq_sessao(struct Sessao *vetor_sessao, int *num_sessoes);
void fecha_arq_sala(Sala *vetor_sala, int *num_salas);
void fecha_arq_filme(Filme *vetor_filme, int *num_filmes);
void fecha_arq_sessao(Sessao *vetor_sessao, int *num_sessoes);

//fun��es Sala
int buscar_sala(struct Sala vetor_sala[], int num_salas, int cod_sala);
int inserir_sala(struct Sala vetor_sala[], int *num_salas);                    
void listar_uma_sala(struct Sala vetor_sala[], int num_salas);
void imprime_sala(struct Sala vetor_sala[], int num_salas, int cod_sala);
void listar_salas(struct Sala vetor_sala[], int num_salas);
void alterar_sala(struct Sala vetor_sala[], int num_salas);
int excluir_sala(struct Sala vetor_sala[], int *num_salas);

//fun��es Filme
int buscar_filme(struct Filme vetor_filme[], int num_filmes, int cod_filme);
int inserir_filme(struct Filme vetor_filme[], int *num_filmes);
void listar_um_filme(struct Filme vetor_filme[], int num_filmes);
void imprime_filme(struct Filme vetor_filme[], int num_filmes, int cod_filme);
void listar_filmes(struct Filme vetor_filme[],int num_filmes);
void alterar_filme(struct Filme vetor_filme[],int num_filmes);
int excluir_filme(struct Filme vetor_filme[], int *num_filmes);

//Fun��es Sess�o
int buscar_sessao(struct Sessao vetor_sessao[], int num_sessoes, int cod_sala, int cod_filme, int dia, int mes, int ano, int hora, int minuto);
int inserir_sessao(struct Sessao vetor_sessao[], struct Sessao nova_sessao, struct Sala vetor_sala[], struct Filme vetor_filme[], int *num_sessoes, int *num_salas, int *num_filmes);
void listar_uma_sessao(struct Sessao vetor_sessao[], int num_sessoes);
void imprime_sessao(struct Sessao vetor_sessao[], int num_sessoes, int cod_sala, int cod_filme);
void listar_sessoes(struct Sessao vetor_sessao[], int num_sessoes);
void alterar_sessao(struct Sessao vetor_sessao[], int num_sessoes);
int excluir_sessao(struct Sessao vetor_sessao[], int *num_sessoes);

//Fun��es Relat�rio
void buscar_dados_salas_exibicao_e_capacidade(struct Sala vetor_sala[], int num_salas);
void dados_filmes_a_partir_do_ano_de_lancamento(struct Filme vetor_filme[], int num_filmes);
void listar_sessao_a_partir_da_data(struct Sessao vetor_sessao[], int num_sessoes, struct Sala vetor_sala[], struct Filme vetor_filme[], int num_salas, int num_filmes);


//--------------------------------- Arquivos ------------------------------------------

void abre_arq_sala(struct Sala *vetor_sala, int *num_salas){    
	FILE *fp;
	int capacidade = max_salas;
	int flagp, op;
	
	if ((fp = fopen("arq_sala.dat", "rb")) == NULL){
		printf("O arquivo de Salas ainda n�o foi criado! Voc� deseja criar um novo? 1- Sim, 2- N�o.\n");
		scanf("%d", &op);
		if (op == 1){
			if ((fp = fopen("arq_sala.dat", "wb+")) != NULL)
				printf("O arquivo de salas foi criado com sucesso!\n\n");
		}
		else
            exit(1);
	}	
	
	while (!feof(fp)){ 
		flagp = fread(&vetor_sala[*num_salas], sizeof(Sala), 1, fp);
		*num_salas += flagp;
		if (*num_salas == capacidade){
			capacidade += 5;
			vetor_sala = (Sala *) realloc (vetor_sala, capacidade * sizeof(Sala));
		}
	}
	
	rewind(fp);
    fclose(fp);
}


void abre_arq_filme(struct Filme *vetor_filme, int *num_filmes){    
	FILE *fp;
	int capacidade = max_filmes;
	int flagp, op;
	
	if ((fp = fopen("arq_filme.dat", "rb")) == NULL){
		printf("O arquivo de Filmes ainda n�o foi criado! Voc� deseja criar um novo? 1- Sim, 2- N�o.\n");
		scanf("%d", &op);
		if (op == 1){
			if ((fp = fopen("arq_filme.dat", "wb+")) != NULL)
				printf("O arquivo de filmes foi criado com sucesso!\n\n");
		}
		else
            exit(1);
	}
	
	while (!feof(fp)){ 
		flagp = fread(&vetor_filme[*num_filmes], sizeof(Filme), 1, fp);
		*num_filmes += flagp;
		if (*num_filmes == capacidade){
			capacidade += 5;
			vetor_filme = (Filme *) realloc (vetor_filme, capacidade * sizeof(Filme));
			
		}
	}
	
	rewind(fp);
    fclose(fp);
}


void abre_arq_sessao(struct Sessao *vetor_sessao, int *num_sessoes){    
	FILE *fp;
	int capacidade = max_sessoes;
	int flagp, op;
	
	if ((fp = fopen("arq_sessao.dat", "rb")) == NULL){
		printf("O arquivo de Sess�es ainda n�o foi criado! Voc� deseja criar um novo? 1- Sim, 2- N�o.\n");
		scanf("%d", &op);
		if (op == 1){
			if ((fp = fopen("arq_sessao.dat", "wb+")) != NULL)
				printf("O arquivo de sess�es foi criado com sucesso!\n\n");
		}
		else
            exit(1);
	}
	
	while (!feof(fp)){ 
		flagp = fread(&vetor_sessao[*num_sessoes], sizeof(Sessao), 1, fp);
		*num_sessoes += flagp;
		if (*num_sessoes == capacidade){
			capacidade += 5;
			vetor_sessao = (Sessao *) realloc (vetor_sessao, capacidade * sizeof(Sessao));	
		}
	}
	
	rewind(fp);
    fclose(fp);
}



void fecha_arq_sala(Sala *vetor_sala, int *num_salas){ //Grava o vetor no arquivo de salas e fecha
    FILE *fp;
	
	if((fp = fopen("arq_sala.dat", "wb")) == NULL){
		printf("Erro na cria��o do arquivo.\n");
		exit(1);
	}
	
	if(fwrite(vetor_sala, sizeof(Sala), *num_salas, fp) != *num_salas){
		printf("Erro ao gravar no arquivo!\n");
		exit(1);
	}
		
	rewind(fp);
    fclose(fp);
}


void fecha_arq_filme(Filme *vetor_filme, int *num_filmes){
	FILE *fp;
	
	if ((fp = fopen("arq_filme.dat", "wb")) == NULL) {
		printf("Erro na cria��o do arquivo.\n");
		exit(1);
	}
	
	if (fwrite(vetor_filme, sizeof(Filme), *num_filmes, fp) != *num_filmes){
		printf("Erro ao gravar no arquivo!\n");
		exit(1);
	}
	
	rewind(fp);
	fclose(fp);
}


void fecha_arq_sessao(Sessao *vetor_sessao, int *num_sessoes){
	FILE *fp;
	
	if((fp = fopen("arq_sessao.dat", "wb")) == NULL){
		printf("Erro na cria��o do arquivo.\n");
		exit(1);
	}
	
	if(fwrite(vetor_sessao, sizeof(Sessao), *num_sessoes, fp) != *num_sessoes){
		printf("Erro ao gravar no arquivo!\n");
		exit(1);
	}	
	
	rewind(fp);
    fclose(fp);	
}


//-------------------------------- Menu - Salas ---------------------------------------
int sub_menu_sala(){
	printf("|-----------------------|\n");
	printf("Adicionar sala..........1\n");
    printf("Listar as salas.........2\n");
    printf("Listar uma sala.........3\n");
    printf("Alterar sala............4\n");
    printf("Excluir sala............5\n");
    printf("Sair....................0\n\n");
    printf("-> ");
    int opcao;
    scanf("%d",&opcao);
    return opcao;
}

void menu_sala(struct Sala vetor_sala[], int *num_salas){
	int op, inseriu, excluiu;
	do{
		op = sub_menu_sala();
		switch(op){
			case 1:    
				inseriu = inserir_sala(vetor_sala, num_salas);                 
				if(inseriu == 1)
					printf("Sala inserida com sucesso!\n\n");
				else
					printf("O c�digo j� est� cadastrado no sistema!\n\n");
				break;
			
			case 2:
				listar_salas(vetor_sala, *num_salas);
				break;
				
			case 3:
				listar_uma_sala(vetor_sala, *num_salas); 
				break;
				
			case 4:
				alterar_sala(vetor_sala, *num_salas);
				break;	
			
			case 5:
				excluiu = excluir_sala(vetor_sala, num_salas);
				if(excluiu == 1)			
					printf("Sala removida com sucesso!\n\n");
				else
					printf("N�o foi poss�vel remover a sala.\n\n");	
				break;
		}	
	} while(op != 0);
}
//-------------------------------------------------------------------------------------


//-------------------------------- Menu - Filmes --------------------------------------
int sub_menu_filme(){
	printf("|-----------------------|\n");
	printf("Adicionar filme.........1\n");
    printf("Listar os filmes........2\n");
    printf("Listar um filme.........3\n");
    printf("Alterar filme...........4\n");
    printf("Excluir filme...........5\n");
    printf("Sair....................0\n\n");
    printf("-> ");
    int opcao;
    scanf("%d",&opcao);
    return opcao;
}

void menu_filme(struct Filme vetor_filme[], int *num_filmes){
	int op, inseriu, excluiu;
	do{
		op = sub_menu_filme();
		switch(op){
			case 1: 
				inseriu = inserir_filme(vetor_filme, num_filmes);  
				if(inseriu == 1)
					printf("Filme inserido com sucesso!\n\n");
				else
					printf("O c�digo j� est� cadastrado no sistema!\n\n");
				break;
			
			case 2:
				listar_filmes(vetor_filme, *num_filmes);
				break;
				
			case 3:
				listar_um_filme(vetor_filme, *num_filmes);

				break;
				
			case 4:
				alterar_filme(vetor_filme, *num_filmes);
				break;	
			
			case 5:
				excluiu = excluir_filme(vetor_filme, num_filmes);
				if(excluiu == 1)			
					printf("Filme removido com sucesso!\n\n");
				else
					printf("N�o foi poss�vel remover o filme.\n\n");
				break;
		}	
	} while(op != 0);
}

//--------------------------------------------------------------------------------------


//-------------------------------- Menu - Sess�es --------------------------------------
int sub_menu_sessao(){
	printf("|-----------------------|\n");
	printf("Adicionar sess�o........1\n");
    printf("Listar as sess�es.......2\n");
    printf("Listar uma sess�o.......3\n");
    printf("Alterar sess�o..........4\n");
    printf("Excluir sess�o..........5\n");
    printf("Sair....................0\n\n");
    printf("-> ");
    int opcao;
    scanf("%d",&opcao);
    return opcao;
}
				
void menu_sessao(struct Sessao vetor_sessao[], struct Sessao nova_sessao, int *num_sessoes, struct Sala vetor_sala[], struct Filme vetor_filme[], int *num_salas, int *num_filmes){
	int op, inseriu, excluiu;
	do{
		op = sub_menu_sessao();
		switch(op){
			case 1:   
				inseriu = inserir_sessao(vetor_sessao, nova_sessao, vetor_sala, vetor_filme, num_sessoes, num_salas, num_filmes);   
				if(inseriu == 1)
					printf("Cadastro de sess�o inserido com sucesso!\n\n");
				else if(inseriu == 2)
					printf("O c�digo do filme n�o est� cadastrado no sistema!\n");
				else if(inseriu == 3)
					printf("O c�digo da sala n�o est� cadastrado no sistema!\n");
				else 
					printf("J� existe uma sess�o nesse hor�rio. Por favor, escolha outra data e hor�rio.\n");
				break;
			
			case 2:
				listar_sessoes(vetor_sessao, *num_sessoes);
				break;
				
			case 3:
				listar_uma_sessao(vetor_sessao, *num_sessoes);
				break;
				
			case 4:
				alterar_sessao(vetor_sessao, *num_sessoes);
				break;	
			
			case 5:
				excluiu = excluir_sessao(vetor_sessao, num_sessoes);
				if(excluiu == 1)			
					printf("Sess�o removida com sucesso!\n\n");
				else
					printf("N�o foi poss�vel remover a sess�o.\n\n");
				break;
		}	
	} while(op != 0);
}

//----------------------------------------------------------------------------

//RELAT�RIOS//

int sub_menu_relatorio(){
	printf("|-------------------------------------------------------------------|\n");
	printf("Dados das salas a partir da exibi��o e da capacidade de pessoas.....1\n");
    printf("Dados dos filmes a partir do ano de lan�amento......................2\n");
    printf("Lista de sess�es a partir da data fornecida.........................3\n");
    printf("Sair................................................................0\n\n");
    printf("-> ");
    int opcao;
    scanf("%d",&opcao);
    return opcao;
}
				
void menu_relatorio(struct Sessao vetor_sessao[], int *num_sessoes, struct Sala vetor_sala[], struct Filme vetor_filme[], int *num_salas, int *num_filmes){
	int op;
	do{
		op = sub_menu_relatorio();
		switch(op){
			case 1:   
				buscar_dados_salas_exibicao_e_capacidade(vetor_sala, *num_salas);  
				break;
			
			case 2:
				dados_filmes_a_partir_do_ano_de_lancamento(vetor_filme, *num_filmes);
				break;
				
			case 3:
				listar_sessao_a_partir_da_data(vetor_sessao, *num_sessoes, vetor_sala, vetor_filme, *num_salas, *num_filmes);
				break;
		}	
	} while(op != 0);
}


void buscar_dados_salas_exibicao_e_capacidade(struct Sala vetor_sala[], int num_salas){
	char exibicao_buscada[40];
	int capacidade_buscada, i, resultado;
	int achei_exibicao = 0;
	FILE *relatorio_um;
	fflush(stdin);
	printf("Insira o tipo de exibi��o do qual voc� quer extrair os dados das salas:\n");
	gets(exibicao_buscada);
	printf("Insira o n�mero de capacidade de pessoas:\n");
	scanf("%d",&capacidade_buscada);
	
	relatorio_um = fopen("relatorio_um.txt","a+");
	if (relatorio_um == NULL) 
		printf("N�o foi possivel abrir o arquivo\n");
	else{
		printf("Relat�rio escrito!\n");
		fprintf(relatorio_um, "Mostrar todos os dados de todas as salas cujo tipo de exibi��o seja X e tenha capacidade para mais de Y pessoas, onde X e Y s�o fornecidos pelo usu�rio:\n\n\n");
		for(i=0;i<num_salas;i++){
			resultado = strcmp(vetor_sala[i].tipo_exibicao, exibicao_buscada);
			if(resultado == 0 && vetor_sala[i].capacidade >= capacidade_buscada){
				achei_exibicao = 1;
				fprintf(relatorio_um, "C�digo: %d\n",vetor_sala[i].codigo);
				fprintf(relatorio_um, "Nome: %s\n", vetor_sala[i].nome);
				fprintf(relatorio_um, "Tipo de exibi��o: %s\n", vetor_sala[i].tipo_exibicao);
				fprintf(relatorio_um, "Acessibilidade: %c\n", vetor_sala[i].acessivel);
				fprintf(relatorio_um, "Capacidade: %d\n\n", vetor_sala[i].capacidade);
				fprintf(relatorio_um, "\n\n");
			}
		}
		if (achei_exibicao == 0){
			printf("N�o foi encontrada nenhuma sala!\n\n");	
		}
		fprintf(relatorio_um,"------------------------------------\n");
		fclose(relatorio_um);
	}
}  

void dados_filmes_a_partir_do_ano_de_lancamento(struct Filme vetor_filme[], int num_filmes){
	int ano_buscado, i, achei = 0;
	FILE *relatorio_dois;
	fflush(stdin);
	printf("Insira o ano de lan�amento do qual voc� quer extrair os dados dos filmes lan�ados a partir desse ano: \n");
	scanf("%d",&ano_buscado);
	
	relatorio_dois = fopen("relatorio_dois.txt","a+");
	fprintf(relatorio_dois, "Mostrar todos os dados de todos os filmes que foram lan�ados a partir do ano X, onde X � fornecido pelo usu�rio\n\n\n");
	for(i=0;i<num_filmes;i++){
		if (relatorio_dois == NULL) 
			printf("N�o foi possivel abrir o arquivo\n\n");
		else{
			if(vetor_filme[i].ano_lancamento >= ano_buscado){
				achei = 1;
				fprintf(relatorio_dois, "C�digo: %d\n",vetor_filme[i].codigo);
				fprintf(relatorio_dois, "Nome: %s\n", vetor_filme[i].nome);
				fprintf(relatorio_dois, "Diretor: %s\n", vetor_filme[i].diretor);
				fprintf(relatorio_dois, "Ano de Lan�amento: %d\n", vetor_filme[i].ano_lancamento);
				fprintf(relatorio_dois, "Atores: \n");
				int j;
				for(j=0;j<vetor_filme[i].posicao_atores;j++){                
					fprintf(relatorio_dois, vetor_filme[i].atores[j]);
					fprintf(relatorio_dois, "\n");
				}	
				fprintf(relatorio_dois, "\n\n");
			}
		}
	}	
	if(achei == 1){
		printf("Relat�rio escrito!\n");
	}	
	fprintf(relatorio_dois,"------------------------------------\n");
	fclose(relatorio_dois);	
}



void listar_sessao_a_partir_da_data(struct Sessao vetor_sessao[], int num_sessoes, struct Sala vetor_sala[], struct Filme vetor_filme[], int num_salas, int num_filmes){
	struct tm data_inicial, data_final;
	int i;
	FILE *relatorio_tres;
	
	relatorio_tres = fopen("relatorio_tres.txt","a+");

	printf("Insira a data inicial e final a seguir: \n\n");
	printf("Insira a data inicial (dia): ");
	scanf("%d", &data_inicial.tm_mday);
	printf("Insira a data inicial (m�s): ");
	scanf("%d", &data_inicial.tm_mon);
	printf("Insira a data inicial (ano): ");
	scanf("%d", &data_inicial.tm_year);
	printf("Insira a data inicial (hora): ");
	scanf("%d", &data_inicial.tm_hour);
	printf("Insira a data inicial (minutos): ");
	scanf("%d", &data_inicial.tm_min);
	data_inicial.tm_year -= 1900; 
	data_inicial.tm_mon -= 1; 

	printf("Insira a data final (dia): ");
	scanf("%d", &data_final.tm_mday);
	printf("Insira a data final (m�s): ");
	scanf("%d", &data_final.tm_mon);
	printf("Insira a data final (ano): ");
	scanf("%d", &data_final.tm_year);
	printf("Insira a data final (hora): ");
	scanf("%d", &data_final.tm_hour);
	printf("Insira a data final (minuto): ");
	scanf("%d", &data_final.tm_min);
	data_final.tm_year -= 1900; 
	data_final.tm_mon -= 1;
	printf("\n");
		
	int j;
	for(j=0;j<num_sessoes;j++){
		vetor_sessao[j].data_hora.tm_year -= 1900;         //ajustando os valores das datas e horas de cada sess�o
		vetor_sessao[j].data_hora.tm_mon -= 1;
	}

	int indice_filme, indice_sala, flag = 0;
	fprintf(relatorio_tres, "Mostrar o c�digo do filme, nome do filme, atores, c�digo da sala, nome da sala e os demais atributos de todas as sess�es exibidas a partir de uma data inicial X at� uma data final Y, onde ambas as datas s�o fornecidas pelo usu�rio: \n\n\n");
	for (i=0;i<num_sessoes;i++){
		if (difftime(mktime(&vetor_sessao[i].data_hora), mktime(&data_inicial)) >= 0 &&     //mktime converte a struct tm em um formato time_t
        	difftime(mktime(&data_final), mktime(&vetor_sessao[i].data_hora)) >= 0){        //difftime para calcular a diferen�a em segundos entre esses valores de tempo
        	fflush(stdin);																	//se for >= 0, a sess�o est� dentro do intervalo de tempo
        	
        	if (relatorio_tres == NULL)
        		printf("N�o foi poss�vel abrir o arquivo\n\n");
        	else{
        		fprintf(relatorio_tres, "|--------------Filme--------------|\n");
				fprintf(relatorio_tres, "C�digo do filme: %d\n", vetor_sessao[i].codigo_filme);
				indice_filme = buscar_filme(vetor_filme, num_filmes, vetor_sessao[i].codigo_filme);     //passa como �ltima refer�ncia o c�digo do filme cadastrado em Sess�o
				fprintf(relatorio_tres, "Nome do filme: %s\n", vetor_filme[indice_filme].nome);    
				fprintf(relatorio_tres, "Atores do filme: \n");
				int j;
				for(j=0;j<vetor_filme[indice_filme].posicao_atores;j++){
					fprintf(relatorio_tres, vetor_filme[indice_filme].atores[j]);
					fprintf(relatorio_tres, "\n");
				}
				fprintf(relatorio_tres, "\n\n");
				
				fprintf(relatorio_tres, "|--------------Sala---------------|\n");
				fprintf(relatorio_tres, "C�digo da sala: %d\n", vetor_sessao[i].codigo_sala);
				indice_sala = buscar_sala(vetor_sala, num_salas, vetor_sessao[i].codigo_sala);         //passa como �ltima refer�ncia o c�digo da sala cadastrada em Sess�o
				fprintf(relatorio_tres, "Nome da sala: %s\n", vetor_sala[indice_sala].nome);
				fprintf(relatorio_tres, "\n\n");
				
				fprintf(relatorio_tres, "|--------------Sess�o-------------|\n");
				fprintf(relatorio_tres, "Data: %d/%d/%d\n", vetor_sessao[i].data_hora.tm_mday, vetor_sessao[i].data_hora.tm_mon, vetor_sessao[i].data_hora.tm_year);
				fprintf(relatorio_tres, "Hor�rio: %d:%d\n", vetor_sessao[i].data_hora.tm_hour, vetor_sessao[i].data_hora.tm_min);
				fprintf(relatorio_tres, "Pre�o do Ingresso: %.2f\n\n", vetor_sessao[i].preco_ingresso);	
				fprintf(relatorio_tres, "\n\n\n");
				flag = 1;
			}
		}	
	}
	if(flag==1){
		printf("Relat�rio escrito!\n");
	}
	fprintf(relatorio_tres,"------------------------------------\n");
	fclose(relatorio_tres);
}	

//----------------------------------------------------------------------------

//------------- Buscar, Inserir, Listar, Excluir, Alterar - Sala --------------

int buscar_sala(struct Sala vetor_sala[], int num_salas, int cod_sala){
	int i;
	for(i=0;i<num_salas;i++){
		if(vetor_sala[i].codigo == cod_sala)
			return i;
	}
	return -1;
}


void listar_uma_sala(struct Sala vetor_sala[], int num_salas){
	if (num_salas > 0){
		int indice, codigo_listar_uma_sala;
		printf("Insira o c�digo da sala que voc� deseja listar: \n");
		scanf("%d",&codigo_listar_uma_sala);
		indice = buscar_sala(vetor_sala,num_salas,codigo_listar_uma_sala);
		
		if (indice == -1)
			printf("C�digo n�o cadastrado!\n\n");
		else{
			imprime_sala(vetor_sala, num_salas, codigo_listar_uma_sala);
		}
	}
	else{
		printf("Ainda n�o h� salas cadastradas!\n\n");
	}
}


int excluir_sala(struct Sala vetor_sala[], int *num_salas){
		int codigo_a_ser_excluido, indice, i;
		printf("Digite o c�digo da sala a ser exclu�da: \n");
		scanf("%d",&codigo_a_ser_excluido);
		indice = buscar_sala(vetor_sala, *num_salas, codigo_a_ser_excluido);
		
		if (indice >= 0){
			for(i=indice; i<*num_salas-1; i++){
				vetor_sala[i] = vetor_sala[i+1];
			}
			(*num_salas)--;
			return 1;
		}
		else{
			return -1;
		}	
}


void alterar_sala(struct Sala vetor_sala[], int num_salas){
	if(num_salas>0){
		int codigo_a_ser_alterado, indice;
		printf("Digite o c�digo da sala a ser alterado: \n");
		scanf("%d",&codigo_a_ser_alterado);
		indice = buscar_sala(vetor_sala, num_salas, codigo_a_ser_alterado);
		
		if(indice == -1)
			printf("C�digo n�o cadastrado!\n");
		else{
			fflush(stdin);
			vetor_sala[indice].codigo = codigo_a_ser_alterado;
			printf("Nome da Sala: \n");
			gets(vetor_sala[indice].nome);
			printf("Tipo de exibi��o: \n");
			gets(vetor_sala[indice].tipo_exibicao);
			printf("� acess�vel? Sim(S) ou N�o(N)? \n");
			scanf("%c",&vetor_sala[indice].acessivel);
			printf("N�mero de capacidade da sala: \n");
			scanf("%d",&vetor_sala[indice].capacidade);
			printf("Sala alterada com sucesso!\n\n");
		}
	}
	else{
		printf("Ainda n�o h� salas cadastradas!\n\n");
	}
}


int inserir_sala(struct Sala vetor_sala[], int *num_salas){
	if (*num_salas<max_salas){
		int indice, codigo_a_ser_comparado;
		printf("Insira os dados da Sala: \n");
		printf("Digite o c�digo: \n");
		scanf("%d",&codigo_a_ser_comparado);
		indice = buscar_sala(vetor_sala, *num_salas, codigo_a_ser_comparado);
		
		if (indice == -1){
			fflush(stdin);
			vetor_sala[*num_salas].codigo = codigo_a_ser_comparado;
			printf("Nome da Sala: \n");
			gets(vetor_sala[*num_salas].nome);
			printf("Tipo de exibi��o: \n");
			gets(vetor_sala[*num_salas].tipo_exibicao);
			printf("� acess�vel? Sim(S) ou N�o(N)? \n");
			scanf("%c",&vetor_sala[*num_salas].acessivel);
			printf("N�mero de capacidade da sala: \n");
			scanf("%d",&vetor_sala[*num_salas].capacidade);
			(*num_salas)++;
			return 1;
		}
		
		else{
			return -1;
		}
	}
}


void listar_salas(struct Sala vetor_sala[], int num_salas){ //imprime todas as salas
	if (num_salas > 0){
		int i;
		for(i=0;i<num_salas;i++){
			printf("C�digo: %d\n",vetor_sala[i].codigo);
			printf("Nome: %s\n", vetor_sala[i].nome);
			printf("Tipo de exibi��o: %s\n", vetor_sala[i].tipo_exibicao);
			printf("Acessibilidade: %c\n", vetor_sala[i].acessivel);
			printf("Capacidade: %d\n\n", vetor_sala[i].capacidade);
		}	
	}
	else{
		printf("N�o h� salas cadastradas!\n\n");
	}
}


void imprime_sala(struct Sala vetor_sala[], int num_salas, int cod_sala){   //imprime uma sala s�
	int i;
	for(i=0;i<num_salas;i++){
		if(vetor_sala[i].codigo == cod_sala){
			printf("C�digo: %d\n",vetor_sala[i].codigo);
			printf("Nome: %s\n", vetor_sala[i].nome);
			printf("Tipo de exibi��o: %s\n", vetor_sala[i].tipo_exibicao);
			printf("Acessibilidade: %c\n", vetor_sala[i].acessivel);
			printf("Capacidade: %d\n\n", vetor_sala[i].capacidade);
		}
	}	
}

//-----------------------------------------------------------------------------

//------------- Buscar, Inserir, Listar, Excluir, Alterar - Filme -------------

int buscar_filme(struct Filme vetor_filme[], int num_filmes, int cod_filme){
	int i;
	for(i=0;i<num_filmes;i++){
		if(vetor_filme[i].codigo == cod_filme)
			return i;
	}
	return -1;
}


void imprime_filme(struct Filme vetor_filme[], int num_filmes, int cod_filme){   //imprime um filme s�
	int i;
	for(i=0;i<num_filmes;i++){
		if(vetor_filme[i].codigo == cod_filme){
			printf("C�digo: %d\n",vetor_filme[i].codigo);
			printf("Nome: %s\n", vetor_filme[i].nome);
			printf("Diretor: %s\n", vetor_filme[i].diretor);
			printf("Ano de Lan�amento: %d\n", vetor_filme[i].ano_lancamento);
			
			printf("Atores: \n");
			int j;
			for(j=0;j<vetor_filme[i].posicao_atores;j++){                //imprime a quantidade de atores daquele determinado filme 
				puts(vetor_filme[i].atores[j]);
			}	
		}
	}
}	


void listar_filmes(struct Filme vetor_filme[],int num_filmes){
	if (num_filmes > 0){
		int i;
		for(i=0;i<num_filmes;i++){
			printf("C�digo: %d\n", vetor_filme[i].codigo);
			printf("Nome: %s\n", vetor_filme[i].nome);
			printf("Diretor: %s\n", vetor_filme[i].diretor);
			printf("Ano de lan�amento: %d\n", vetor_filme[i].ano_lancamento);
			
			printf("Atores: \n");
			int j;
			for(j=0;j<vetor_filme[i].posicao_atores;j++){
				puts(vetor_filme[i].atores[j]);
			}
			printf("\n");
		}
	}
	else{
		printf("N�o h� filmes cadastrados!\n\n");
	}
}


void alterar_filme(struct Filme vetor_filme[],int num_filmes){
	if(num_filmes>0){
		int codigo_a_ser_alterado, indice;
		printf("Digite o c�digo do filme a ser alterado: \n");
		scanf("%d",&codigo_a_ser_alterado);
		indice = buscar_filme(vetor_filme,num_filmes,codigo_a_ser_alterado);
		
		if(indice == -1)
			printf("C�digo n�o cadastrado!\n");
		else{
			fflush(stdin);
			vetor_filme[indice].codigo = codigo_a_ser_alterado;
			printf("Nome do filme: \n");
			gets(vetor_filme[indice].nome);
			printf("Diretor do filme: \n");
			gets(vetor_filme[indice].diretor);
			printf("Ano de Lan�amento: \n");
			scanf("%d",&vetor_filme[indice].ano_lancamento);
			
			int i, qnt_atores;
			printf("Quantos atores voc� deseja adicionar? \n");
			scanf("%d",&qnt_atores);
			for(i=0;i<qnt_atores;i++){
				fflush(stdin);
				printf("Adicione o nome do ator(a): \n");
				gets(vetor_filme[indice].atores[i]);
			}
			vetor_filme[indice].posicao_atores = i;
		}
	}
	else{
		printf("Ainda n�o h� filmes cadastrados!\n\n");
	}
}


int excluir_filme(struct Filme vetor_filme[], int *num_filmes){
	int codigo_a_ser_excluido, indice, i;
	printf("Digite o c�digo do filme a ser exclu�do: \n");
	scanf("%d",&codigo_a_ser_excluido);
	indice = buscar_filme(vetor_filme, *num_filmes, codigo_a_ser_excluido);
	
	if(indice>=0){
		for(i=indice; i<*num_filmes-1;i++){
			vetor_filme[i] = vetor_filme[i+1];
		}
		(*num_filmes)--;
		return 1;
	}
	else{
		return -1;
	}
}


void listar_um_filme(struct Filme vetor_filme[], int num_filmes){
	if (num_filmes > 0){
		int indice, codigo_listar_um_filme;
		printf("Insira o c�digo do filme que voc� deseja listar: \n");
		scanf("%d",&codigo_listar_um_filme);
		indice = buscar_filme(vetor_filme,num_filmes,codigo_listar_um_filme);
		
		if (indice == -1)
			printf("C�digo n�o cadastrado!\n\n");
		else{
			imprime_filme(vetor_filme,num_filmes,codigo_listar_um_filme);
		}
	}
	else{
		printf("Ainda n�o h� filmes cadastrados!\n\n");
	}
}


int inserir_filme(struct Filme vetor_filme[], int *num_filmes){
	if (*num_filmes<max_filmes){
		int indice, codigo_a_ser_comparado;
		printf("Insira os dados do Filme: \n");
		printf("Digite o c�digo: \n");
		scanf("%d",&codigo_a_ser_comparado);
		indice = buscar_filme(vetor_filme, *num_filmes, codigo_a_ser_comparado);
		
		if (indice == -1){
			fflush(stdin);
			vetor_filme[*num_filmes].codigo = codigo_a_ser_comparado;
			printf("Nome do Filme: \n");
			gets(vetor_filme[*num_filmes].nome);
			printf("Diretor do Filme: \n");
			gets(vetor_filme[*num_filmes].diretor);
			printf("Ano de Lan�amento: \n");
			scanf("%d",&vetor_filme[*num_filmes].ano_lancamento);
			
			int i, qnt_atores;
			printf("Quantos atores voc� deseja adicionar? \n");
			scanf("%d",&qnt_atores);
			for(i=0;i<qnt_atores;i++){
				fflush(stdin);
				printf("Adicione o nome do ator(a): \n");
				gets(vetor_filme[*num_filmes].atores[i]);
			}
			
		vetor_filme[*num_filmes].posicao_atores = i;		   //posicao_atores serve como uma len dos atores adicionados em um determinado filme
		(*num_filmes)++;	
		return 1;
		}
		else
			return -1;
	}
}

//----------------------------------------------------------------------------

//------------ Buscar, Inserir, Listar, Excluir, Alterar - Sess�o ------------

int buscar_sessao(struct Sessao vetor_sessao[], int num_sessoes, int cod_sala, int cod_filme, int dia, int mes, int ano, int hora, int minuto){
	int i;
	for(i=0;i<num_sessoes;i++){
		if(vetor_sessao[i].codigo_sala == cod_sala && vetor_sessao[i].codigo_filme == cod_filme &&  
		vetor_sessao[i].data_hora.tm_mday == dia && vetor_sessao[i].data_hora.tm_mon == mes && 
		vetor_sessao[i].data_hora.tm_year == ano && vetor_sessao[i].data_hora.tm_hour == hora &&
		vetor_sessao[i].data_hora.tm_min == minuto)
		{
			return i;
		}
	}
	return -1;
}


void listar_uma_sessao(struct Sessao vetor_sessao[], int num_sessoes){
	if(num_sessoes > 0){
		int indice, cod_sala, cod_filme, dia, mes, ano, hora, minuto;
		printf("Insira o c�digo da sala: \n");
		scanf("%d",&cod_sala);
		printf("Insira o c�digo do filme: \n");
		scanf("%d",&cod_filme);
		printf("Insira o dia: \n");
		scanf("%d", &dia);
		printf("Insira o m�s: \n");
		scanf("%d", &mes);
		printf("Insira o ano: \n");
		scanf("%d", &ano);
		printf("Insira a hora: \n");
		scanf("%d", &hora);
		printf("Insira os minutos: \n");
		scanf("%d", &minuto);
		
		indice = buscar_sessao(vetor_sessao, num_sessoes,cod_sala,cod_filme, dia, mes, ano, hora, minuto);
		if(indice == -1)
			printf("Sess�o n�o cadastrada!\n\n");
		else{
			imprime_sessao(vetor_sessao, num_sessoes, cod_sala, cod_filme);
		}
	}
}


void listar_sessoes(struct Sessao vetor_sessao[], int num_sessoes){
	if(num_sessoes > 0){
		int i;
		for(i=0;i<num_sessoes;i++){
			printf("C�digo da Sala: %d\n", vetor_sessao[i].codigo_sala);
			printf("C�digo da Filme: %d\n", vetor_sessao[i].codigo_filme);
			printf("Data: %d/%d/%d\n", vetor_sessao[i].data_hora.tm_mday, vetor_sessao[i].data_hora.tm_mon, vetor_sessao[i].data_hora.tm_year);
			printf("Hor�rio: %d:%d\n", vetor_sessao[i].data_hora.tm_hour, vetor_sessao[i].data_hora.tm_min);
			printf("Pre�o do Ingresso: %.2f\n\n", vetor_sessao[i].preco_ingresso);
		}
	}
	else{
		printf("N�o h� sess�es cadastradas!\n\n");
	}
}


int excluir_sessao(struct Sessao vetor_sessao[], int *num_sessoes){
	int i, indice, cod_sala, cod_filme, dia, mes, ano, hora, minuto;
	printf("Insira o c�digo da sala: \n");
	scanf("%d",&cod_sala);
	printf("Insira o c�digo do filme: \n");
	scanf("%d",&cod_filme);
	printf("Insira o dia: \n");
	scanf("%d", &dia);
	printf("Insira o m�s: \n");
	scanf("%d", &mes);
	printf("Insira o ano: \n");
	scanf("%d", &ano);
	printf("Insira a hora: \n");
	scanf("%d", &hora);
	printf("Insira os minutos: \n");
	scanf("%d", &minuto);
	
	indice = buscar_sessao(vetor_sessao, *num_sessoes,cod_sala,cod_filme, dia, mes, ano, hora, minuto);
	if (indice >= 0){
		for(i=indice;i<*num_sessoes-1;i++){
			vetor_sessao[i] = vetor_sessao[i+1];
		}
		(*num_sessoes)--;
		return 1;
	}
	else{
		return -1;
	}
}


void imprime_sessao(struct Sessao vetor_sessao[], int num_sessoes, int cod_sala, int cod_filme){
	int i;
	for(i=0;i<num_sessoes;i++){
		if(vetor_sessao[i].codigo_sala == cod_sala && vetor_sessao[i].codigo_filme == cod_filme){
			printf("C�digo da Sala: %d\n", vetor_sessao[i].codigo_sala);
			printf("C�digo do Filme: %d\n", vetor_sessao[i].codigo_filme);
			printf("Data: %d/%d/%d\n", vetor_sessao[i].data_hora.tm_mday, vetor_sessao[i].data_hora.tm_mon, vetor_sessao[i].data_hora.tm_year);
			printf("Hor�rio: %d:%d\n", vetor_sessao[i].data_hora.tm_hour, vetor_sessao[i].data_hora.tm_min);
			printf("Pre�o do Ingresso: %.2f\n\n", vetor_sessao[i].preco_ingresso);
		}	
	}	
}


void alterar_sessao(struct Sessao vetor_sessao[], int num_sessoes){
	if(num_sessoes>0){
		int i, indice, cod_sala, cod_filme, dia, mes, ano, hora, minuto;
		printf("Insira o c�digo da sala: \n");
		scanf("%d",&cod_sala);
		printf("Insira o c�digo do filme: \n");
		scanf("%d",&cod_filme);
		printf("Insira o dia: \n");
		scanf("%d", &dia);
		printf("Insira o m�s: \n");
		scanf("%d", &mes);
		printf("Insira o ano: \n");
		scanf("%d", &ano);
		printf("Insira a hora: \n");
		scanf("%d", &hora);
		printf("Insira os minutos: \n");
		scanf("%d", &minuto);
		
		indice = buscar_sessao(vetor_sessao, num_sessoes,cod_sala,cod_filme, dia, mes, ano, hora, minuto);
		if(indice == -1){
			printf("Sess�o n�o cadastrada!\n");
		}
		else{
			int cod_sala_alt, cod_filme_alt, dia_alt, mes_alt, ano_alt, hora_alt, minuto_alt;
			printf("Insira os novos dados: \n\n");
			printf("Insira o c�digo da sala: \n");
			scanf("%d",&cod_sala_alt);
			printf("Insira o c�digo do filme: \n");
			scanf("%d",&cod_filme_alt);
			printf("Insira o dia: \n");
			scanf("%d", &dia_alt);
			printf("Insira o m�s: \n");
			scanf("%d", &mes_alt);
			printf("Insira o ano: \n");
			scanf("%d", &ano_alt);
			printf("Insira a hora: \n");
			scanf("%d", &hora_alt);
			printf("Insira os minutos: \n");
			scanf("%d", &minuto_alt);
			
			//adicionando novo c�digo de sala e de filme e nova data/hor�rio
			vetor_sessao[indice].codigo_sala = cod_sala_alt;
			vetor_sessao[indice].codigo_filme == cod_filme_alt;
			vetor_sessao[indice].data_hora.tm_mday == dia_alt;
			vetor_sessao[indice].data_hora.tm_mon == mes_alt;
			vetor_sessao[indice].data_hora.tm_year == ano_alt;
			vetor_sessao[indice].data_hora.tm_hour == hora_alt;
			vetor_sessao[indice].data_hora.tm_min == minuto_alt;
			printf("Sess�o alterada com sucesso!\n\n");
		}
	}
	else{
		printf("Ainda n�o h� salas cadastradas!\n\n");
	}
}


int inserir_sessao(struct Sessao vetor_sessao[], struct Sessao nova_sessao, struct Sala vetor_sala[], struct Filme vetor_filme[], int *num_sessoes, int *num_salas, int *num_filmes){
	if (*num_sessoes<max_sessoes){
		int check_sala, codigo_sala_check, check_filme, codigo_filme_check;
		printf("Dados da Sess�o a serem inseridos: \n\n");
		printf("Informe o C�digo da Sala: \n");
		scanf("%d", &codigo_sala_check);
		check_sala = buscar_sala(vetor_sala,*num_salas,codigo_sala_check);
		
		if (check_sala != -1){
			printf("Informe o C�digo do Filme: \n");
			scanf("%d",&codigo_filme_check);
			check_filme = buscar_filme(vetor_filme,*num_filmes,codigo_filme_check);	
			if (check_filme != -1){
				printf("Informe o dia da sess�o (Formato = DD): \n");
				scanf("%d", &nova_sessao.data_hora.tm_mday);
				printf("Informe o m�s da sess�o (Formato = MM): \n");
				scanf("%d", &nova_sessao.data_hora.tm_mon);
				printf("Informe o ano da sess�o (Formato = AAAA): \n");
				scanf("%d", &nova_sessao.data_hora.tm_year);
				printf("Informe a hora da sess�o (Formato = HH): \n");
				scanf("%d", &nova_sessao.data_hora.tm_hour);
				printf("Informe os minutos da sess�o (Formato = MM): \n");
				scanf("%d", &nova_sessao.data_hora.tm_min);
				
				//comparando se existe sess�es no mesmo hor�rio e no mesmo dia
				int i;
				for (i=0; i<*num_sessoes; i++){
				    if (vetor_sessao[i].data_hora.tm_mday == nova_sessao.data_hora.tm_mday &&
				        vetor_sessao[i].data_hora.tm_mon == nova_sessao.data_hora.tm_mon &&
				        vetor_sessao[i].data_hora.tm_year == nova_sessao.data_hora.tm_year &&
				        vetor_sessao[i].data_hora.tm_hour == nova_sessao.data_hora.tm_hour &&
				        vetor_sessao[i].data_hora.tm_min == nova_sessao.data_hora.tm_min){
				        return -1;
				    }
				}
				
				//adicionando informa��es ao vetor_sessao
				vetor_sessao[*num_sessoes].codigo_sala = codigo_sala_check;
				vetor_sessao[*num_sessoes].codigo_filme = codigo_filme_check;
				printf("Digite o pre�o do ingresso da Sess�o: \n");
				scanf("%f",&vetor_sessao[*num_sessoes].preco_ingresso);
				vetor_sessao[*num_sessoes].data_hora = nova_sessao.data_hora;
				(*num_sessoes)++;	
				return 1;
			}
			else{
				return 2;
			}
		}
		else{
			return 3;
		}		
	}
}


main(){
	setlocale(LC_ALL,"Portuguese");
    int opcao;

	Sala *vetor_sala;
	int num_salas = 0;
	vetor_sala = (Sala *) malloc(max_salas * sizeof(Sala));
	abre_arq_sala(vetor_sala, &num_salas);
	
	Filme *vetor_filme;
	int num_filmes = 0;
	vetor_filme = (Filme *) malloc(max_filmes * sizeof(Filme));
	abre_arq_filme(vetor_filme, &num_filmes);
	
	Sessao *vetor_sessao;
	int num_sessoes = 0;
	vetor_sessao = (Sessao *) malloc(max_sessoes * sizeof(Sessao));
	abre_arq_sessao(vetor_sessao, &num_sessoes);
	
    struct Sessao nova_sessao;

    do {
    	printf("|----------------|\n");
		printf("  Menu de op��es  \n");
		printf("|----------------|\n");
		printf("1. Salas\n");
		printf("2. Filmes\n");
		printf("3. Sess�es\n");
		printf("4. Relat�rios\n");
		printf("5. Sair\n\n");
		printf("-> ");
		scanf("%d",&opcao);
		fflush(stdin);

        switch (opcao) {
            case 1:
                menu_sala(vetor_sala, &num_salas); 
                fecha_arq_sala(vetor_sala, &num_salas);
                break;
            case 2:
                menu_filme(vetor_filme, &num_filmes);
                fecha_arq_filme(vetor_filme, &num_filmes);
                break;
            case 3:
            	menu_sessao(vetor_sessao, nova_sessao, &num_sessoes, vetor_sala, vetor_filme, &num_salas, &num_filmes);
            	fecha_arq_sessao(vetor_sessao, &num_sessoes);
                break;
            case 4:
                menu_relatorio(vetor_sessao, &num_sessoes, vetor_sala, vetor_filme, &num_salas, &num_filmes);
                break;
            case 5:
                printf("Obrigado por utilizar o programa!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 5);
    
    free(vetor_sala);
    free(vetor_filme);
    free(vetor_sessao);
}

