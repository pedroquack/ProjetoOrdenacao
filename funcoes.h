#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

typedef struct {
	long long comparacoes;
	long long movimentacoes;
	double tempo_execucao;
} Metricas;

typedef struct {
	int matricula;
	char nome[50];
	float nota;
	int faltas;
} Aluno;

bool compararNome(Aluno alunoA, Aluno alunoB){
	if(strcmp(alunoA.nome, alunoB.nome) > 0){
		return true;
	}else{
		return false;
	}
}

bool compararNotaCrescente(Aluno alunoA, Aluno alunoB){
	if(alunoA.nota > alunoB.nota){
		return true;
	}else{
		return false;
	}
}

bool compararNotaDecrescente(Aluno alunoA, Aluno alunoB){
	if(alunoA.nota < alunoB.nota){
		return true;
	}else{
		return false;
	}
}

bool compararFaltas(Aluno alunoA, Aluno alunoB){
	if(alunoA.faltas < alunoB.faltas){
		return true;
	}else{
		return false;
	}
}

bool compararCombinado(Aluno alunoA, Aluno alunoB){
	if(alunoA.nota < alunoB.nota){
		return true;	
	}
	
	if(alunoA.nota > alunoB.nota){
		return false;
	}
	
	if(alunoA.faltas > alunoB.faltas){
		return true;
	}
	
	if(alunoA.faltas < alunoB.faltas){
		return false;
	}
	
	if(strcmp(alunoA.nome, alunoB.nome) > 0){
		return true;
	}else{
		return false;
	}
}

void trocar(Aluno *alunoA, Aluno *alunoB, Metricas *metricas){
	Aluno temp = *alunoA;
	*alunoA = *alunoB;
	*alunoB = temp;
	metricas->movimentacoes += 3;
}

//Bubble
void bubbleSort(Aluno *alunos, int quantidadeAlunos, bool(*funcaoComparar)(Aluno, Aluno), Metricas *metricas){
	metricas->comparacoes = 0;
	metricas->movimentacoes = 0;
	clock_t inicio = clock();
	bool trocou;
	
	for(int i = 0; i < quantidadeAlunos - 1; i++){
		trocou = false;
		for(int j = 0; j < quantidadeAlunos - i - 1; j++){
			metricas->comparacoes++;
			if(funcaoComparar(alunos[j], alunos[j + 1])){
				trocar(&alunos[j], &alunos[j + 1], metricas);
				trocou = true;
			}
		}
		
		//Se não trocou quer dizer que já está ordenado
		if(trocou == false){
			break;
		}
	}
	
	clock_t fim = clock();
	metricas->tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
}

//Selection
void selectionSort(Aluno *alunos, int quantidadeAlunos, bool(*funcaoComparar)(Aluno, Aluno), Metricas *metricas){
	metricas->comparacoes = 0;
	metricas->movimentacoes = 0;
	clock_t inicio = clock();
	
	for(int i = 0; i < quantidadeAlunos - 1; i ++){
		int menor = i;
		for(int j = i + 1; j < quantidadeAlunos; j++){
			metricas->comparacoes++;
			if(funcaoComparar(alunos[j], alunos[menor])){
				menor = j;
			}
		}
		trocar(&alunos[i], &alunos[menor], metricas);
	}
	
	clock_t fim = clock();
	metricas->tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
}

//Insertion
void insertionSort(Aluno *alunos, int quantidadeAlunos, bool(*funcaoComparar)(Aluno, Aluno), Metricas *metricas){
	metricas->comparacoes = 0;
	metricas->movimentacoes = 0;
	clock_t inicio = clock();
	
	for(int i = 1; i < quantidadeAlunos - 1; i ++){
		Aluno chave = alunos[i];
		metricas->movimentacoes++;
		int j = i - 1;
		
		while(j >= 0){
			metricas->comparacoes++;
			if(funcaoComparar(alunos[j], chave)){
				alunos[j + 1] = alunos[j];
				metricas->movimentacoes++;
				j--;
			}else{
				break;
			}
		}
		
		alunos[j + 1] = chave;
		metricas->movimentacoes++;
		
	}
	
	clock_t fim = clock();
	metricas->tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
}

//Quick

int particao(Aluno *alunos, int baixo, int alto, bool(*funcaoComparar)(Aluno, Aluno), Metricas *metricas){
	Aluno pivo = alunos[alto];
	metricas->movimentacoes++;
	
	int i = (baixo - 1);
	
	for(int j = baixo; j < alto; j++){
		metricas->comparacoes++;
		
		if(funcaoComparar(pivo, alunos[j])){
			i++;
			trocar(&alunos[i], &alunos[j], metricas);
		}
	}
	trocar(&alunos[i + 1], & alunos[alto], metricas);
	return (i + 1);
}

void quickSortRecursao(Aluno *alunos, int baixo, int alto, bool(*funcaoComparar)(Aluno, Aluno), Metricas *metricas){
	if(baixo < alto){
		int pivo = particao(alunos, baixo, alto, funcaoComparar, metricas);
		
		quickSortRecursao(alunos, baixo, pivo - 1, funcaoComparar, metricas);
		quickSortRecursao(alunos, pivo + 1, alto, funcaoComparar, metricas);
	}
}


//Foi separado em duas funções para as metricas não se perderem
void quickSort(Aluno *alunos, int quantidadeAlunos, bool(*funcaoComparar)(Aluno, Aluno), Metricas *metricas) {
    metricas->comparacoes = 0;
    metricas->movimentacoes = 0;
    clock_t inicio = clock();

    if (quantidadeAlunos > 0) {
        quickSortRecursao(alunos, 0, quantidadeAlunos - 1, funcaoComparar, metricas);
    }

    clock_t fim = clock();
    metricas->tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
}

//Merge

void merge(Aluno *alunos, int inicio, int meio ,int fim, bool(*funcaoComparar)(Aluno, Aluno), Metricas *metricas){
	int i, j, k;
	int n1 = meio - inicio + 1;
	int n2 = fim - meio;
	
	Aluno *alunosEsquerda = (Aluno *)malloc(n1 * sizeof(Aluno));
    Aluno *alunosDireita = (Aluno *)malloc(n2 * sizeof(Aluno));
    
    for (i = 0; i < n1; i++) {
        alunosEsquerda[i] = alunos[inicio + i];
        metricas->movimentacoes++;
    }
    for (j = 0; j < n2; j++) {
        alunosDireita[j] = alunos[meio + 1 + j];
        metricas->movimentacoes++;
    }
    
    i = 0;
    j = 0;
    k = inicio;
    
    while(i < n1 && j < n2){
    	metricas->comparacoes++;
    	
    	if(funcaoComparar(alunosEsquerda[i], alunosDireita[j])){
    		alunos[k] = alunosDireita[j];
    		j++;
		}else{
			alunos[k] = alunosEsquerda[i];
			i++;
		}
		metricas->movimentacoes++;
		k++;
	}
	
	while (i < n1) {
        alunos[k] = alunosEsquerda[i];
        i++;
        k++;
        metricas->movimentacoes++;
    }
    
    while (j < n2) {
        alunos[k] = alunosDireita[j];
        j++;
        k++;
        metricas->movimentacoes++;
    }
    
    free(alunosEsquerda);
    free(alunosDireita);
}

void mergeSortRecursao(Aluno *alunos, int inicio, int fim, bool(*funcaoComparar)(Aluno, Aluno), Metricas *metricas) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;

        mergeSortRecursao(alunos, inicio, meio, funcaoComparar, metricas);
        mergeSortRecursao(alunos, meio + 1, fim, funcaoComparar, metricas);

        merge(alunos, inicio, meio, fim, funcaoComparar, metricas);
    }
}

void mergeSort(Aluno *alunos, int quantidadeAlunos, bool(*funcaoComparar)(Aluno, Aluno), Metricas *metricas) {
    metricas->comparacoes = 0;
    metricas->movimentacoes = 0;
    clock_t inicio = clock();

    if (quantidadeAlunos > 1) {
        mergeSortRecursao(alunos, 0, quantidadeAlunos - 1, funcaoComparar, metricas);
    }

    clock_t fim = clock();
    metricas->tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
}


