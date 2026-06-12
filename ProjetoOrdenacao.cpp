#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "./funcoes.h"

int escolherCriterioOrdenacao(){
	int opcao;
	system("cls");
	do{
		printf(" - Criterio de ordenacao - \n");
		printf("(1) - Nota Crescente\n");
		printf("(2) - Nota Descrescente\n");
		printf("(3) - Nomes por Ordem Alfabetica\n");
		printf("(4) - Faltas (Decrescente)\n");
		printf("(5) - Criterio combinado\n");
		printf("Escolha uma opcao: ");
		scanf("%d", &opcao);
	}while(opcao < 1 && opcao > 5);
	
	return opcao;
}

int escolherMetodoOrdenacao(){
	int opcao;
	system("cls");
	do{
		printf(" - Metodos de ordenacao - \n");
		printf("(1) - Bubble Sort\n");
		printf("(2) - Selection Sort\n");
		printf("(3) - Insertion Sort\n");
		printf("(4) - Quick Sort\n");
		printf("(5) - Merge Sort\n");
		printf("Escolha uma opcao: ");
		scanf("%d", &opcao);
	}while(opcao < 1 && opcao > 5);
	
	return opcao;
}

int menu(int criterioOrdenacao){
	int opcao;
	system("cls");
	printf("- Positivo -\n");
	printf("- (1) - Escolher criterio de ordenacao\n");
	printf("- (2) - Selecionar metodo de ordenacao\n");
	printf("- (3) - Exibir desordenado\n");
	printf("- Criterio de ordenacao selecionado : ");
	switch(criterioOrdenacao){
		case 1: printf("Nota Crescente\n"); break;
		case 2: printf("Nota Decrescente\n"); break;
		case 3: printf("Nome\n"); break;
		case 4: printf("Faltas (Decrencente)\n"); break;
		case 5: printf("Combinado\n"); break;
	}
	printf("Escolha uma opcao: ");
	scanf("%d", &opcao);
	return opcao;
}

void exibirAlunos(Aluno *alunos, int quantidadeAlunos){
	printf("| %10s | %30s | %5s | %8s |\n", "Matricula", "Nome", "Nota", "Faltas");
	for(int i = 0; i < quantidadeAlunos; i++){
		printf("| %10d | %30s | %5.2f | %8d |\n", alunos[i].matricula, alunos[i].nome, alunos[i].nota, alunos[i].faltas);
	}
}

void salvarAlunos(Aluno *alunos, int quantidadeAlunos){
    FILE *arquivo_ptr = fopen("alunos_ordenados.txt", "w");

    if(arquivo_ptr == NULL){
        printf("Erro ao criar o arquivo alunos_ordenados.txt\n");
        return;
    }

    for(int i = 0; i < quantidadeAlunos; i++){
        fprintf(arquivo_ptr, "%d;%s;%.2f;%d\n",
                alunos[i].matricula,
                alunos[i].nome,
                alunos[i].nota,
                alunos[i].faltas);
    }

    fclose(arquivo_ptr);
}


void ordenar(Aluno *alunos, int quantidadeAlunos, int metodoOrdenacao, bool (*funcaoComparar)(Aluno, Aluno)){
	
	Aluno *tempAlunos = (Aluno*) malloc(quantidadeAlunos * sizeof(Aluno));
    if (tempAlunos == NULL) {
        printf("Erro de memória!\n");
        return;
    }
    
    memcpy(tempAlunos, alunos, quantidadeAlunos * sizeof(Aluno));
	
	Metricas metricas = {0, 0, 0.0}; 
	
	switch(metodoOrdenacao){
		case 1:
			bubbleSort(tempAlunos, quantidadeAlunos, funcaoComparar, &metricas);
		break;
		case 2:
			selectionSort(tempAlunos, quantidadeAlunos, funcaoComparar, &metricas);
		break;
		case 3:
			insertionSort(tempAlunos, quantidadeAlunos, funcaoComparar, &metricas);
		break;
		case 4:
			quickSort(tempAlunos, quantidadeAlunos, funcaoComparar, &metricas);
		break;
		case 5:
			mergeSort(tempAlunos, quantidadeAlunos, funcaoComparar, &metricas);
		break;
	}
	
	exibirAlunos(tempAlunos, quantidadeAlunos);
	salvarAlunos(tempAlunos, quantidadeAlunos);
	printf("---- METRICAS ----\n");
	printf("Comparacoes: %lld\n", metricas.comparacoes);
	printf("Movimentacoes: %lld\n", metricas.movimentacoes);
	printf("Tempo de execucao: %f\n", metricas.tempo_execucao);
	system("pause");
	system("cls");
}

int main(){
	
	int opcao;
	bool (*funcaoComparar)(Aluno, Aluno) = compararNotaDecrescente;
	int criterioOrdenacao = 2;
	int metodoOrdenacao = 1;
	Aluno *alunos = NULL;
	int quantidadeAlunos = 0;
	
	FILE *arquivo_ptr = fopen("alunos.txt", "r");
	char buffer[200];
	
	if(arquivo_ptr == NULL){
		printf("Houve um erro ao ler o arquivo de alunos...\n");
		system("pause");
		return 0;
	}
	
	//Primeiro tem que pegar a quantidade de alunos que tem no arquivo
	while (fgets(buffer, sizeof(buffer), arquivo_ptr)) {
        quantidadeAlunos++;
    }
	
	//Isso volta a leitura do arquivo pro começo, pra dai sim começar a alocar os alunos
	rewind(arquivo_ptr);
	
	//Aloca a memoria dos alunos de acordo com a quantidade
	alunos = (Aluno *) malloc(quantidadeAlunos * sizeof(Aluno));
    if (alunos == NULL) {
        printf("Erro ao alocar memoria dos alunos!\n");
        fclose(arquivo_ptr);
        return 1;
    }
    
    //Pra cada aluno alocado, pega o valor da linha no arquivo e adiciona no aluno
    for (int i = 0; i < quantidadeAlunos; i++) {
        fscanf(arquivo_ptr, "%d;%49[^;];%f;%d\n", 
               &alunos[i].matricula, 
               alunos[i].nome, 
               &alunos[i].nota, 
               &alunos[i].faltas);
    }

	do{
		opcao = menu(criterioOrdenacao);
		
		switch(opcao){
			case 1: 
				criterioOrdenacao = escolherCriterioOrdenacao();
				switch(criterioOrdenacao){
					case 1: funcaoComparar = compararNotaCrescente; break;
					case 2: funcaoComparar = compararNotaDecrescente; break;
					case 3: funcaoComparar = compararNome; break;
					case 4: funcaoComparar = compararFaltas; break;
					case 5: funcaoComparar = compararCombinado; break;
				}
				printf("\nCriterio atualizado!\n");
                system("pause");
			break;
			case 2:
				metodoOrdenacao = escolherMetodoOrdenacao();
				ordenar(alunos, quantidadeAlunos, metodoOrdenacao, funcaoComparar);
			break;
			case 3:
				exibirAlunos(alunos, quantidadeAlunos);
				system("pause");
			break;
		}
	}while(opcao != 0);
	
	fclose(arquivo_ptr);
    free(alunos);
}
