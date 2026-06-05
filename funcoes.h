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

void bubbleSort(Aluno *alunos, int quantidadeAlunos, bool(*funcaoComparar)(Aluno, Aluno), Metricas *metricas){
	metricas->comparacoes = 0;
	metricas->movimentacoes = 0;
	clock_t inicio = clock();
	
	for(int i = 0; i < quantidadeAlunos - 1; i++){
		for(int j = 0; j < quantidadeAlunos - i - 1; j++){
			metricas->comparacoes++;
			if(funcaoComparar(alunos[j], alunos[j + 1])){
				trocar(&alunos[j], &alunos[j + 1], metricas);
			}
		}
	}
	
	clock_t fim = clock();
	metricas->tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
}


