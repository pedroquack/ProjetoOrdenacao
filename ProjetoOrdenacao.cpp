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
	system("pause");
	system("cls");
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
	}
	
	printf("---- METRICAS ----\n");
	printf("Comparacoes: %lld\n", metricas.comparacoes);
	printf("Movimentacoes: %lld\n", metricas.movimentacoes);
	printf("Tempo de execucao: %f\n", metricas.tempo_execucao);
	exibirAlunos(tempAlunos, quantidadeAlunos);
}

void preencherAlunos(Aluno **alunos, int quantidadeAlunos){
	*alunos = (Aluno*) malloc(quantidadeAlunos * sizeof(Aluno));

    if (alunos == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }

    Aluno *a = *alunos;

    a[0] = (Aluno){202301, "Ana Silva", 9.5, 2};
    a[1] = (Aluno){202302, "Bruno Souza", 9.5, 5};
    a[2] = (Aluno){202303, "Carlos Oliveira", 10.0, 1};
    a[3] = (Aluno){202304, "Daniel Costa", 4.5, 15};
    a[4] = (Aluno){202305, "Eduarda Lima", 7.0, 3};
    a[5] = (Aluno){202306, "Fernanda Rocha", 8.5, 4};
    a[6] = (Aluno){202307, "Gabriel Santos", 9.5, 8};
    a[7] = (Aluno){202308, "Helena Farias", 0.0, 25};
    a[8] = (Aluno){202309, "Igor Batista", 10.0, 0};
    a[9] = (Aluno){202310, "Julia Almeida", 9.5, 5};
}

int main(){
	int opcao;
	bool (*funcaoComparar)(Aluno, Aluno) = compararNotaDecrescente;
	
	Aluno *alunos;
	int quantidadeAlunos = 10;
	int criterioOrdenacao = 3;
	int metodoOrdenacao = 1;
	preencherAlunos(&alunos, quantidadeAlunos);
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
			break;
		}
	}while(opcao != 0);
}
