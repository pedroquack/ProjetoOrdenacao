import random
from faker import Faker

# Inicializa o Faker (usando pt_BR para nomes brasileiros)
fake = Faker('en_US')

def gerar_alunos(quantidade):
    nome_arquivo = "alunos.txt"
    
    # Gerar uma lista de matrículas únicas
    # Criamos um range maior que a quantidade para garantir números variados
    matriculas = random.sample(range(100000, 999999), quantidade)
    
    try:
        with open(nome_arquivo, "w", encoding="utf-8") as arquivo:
            for i in range(quantidade):
                matricula = matriculas[i]
                nome = fake.name()
                # Nota entre 0.0 e 10.0 com uma casa decimal
                nota = round(random.uniform(0, 10), 1)
                # Faltas entre 0 e 30
                faltas = random.randint(0, 30)
                
                # Formata a linha conforme solicitado: matricula;nome;nota;faltas
                linha = f"{matricula};{nome};{nota};{faltas}\n"
                arquivo.write(linha)
                
        print(f"Sucesso! Arquivo '{nome_arquivo}' gerado com {quantidade} alunos.")
        
    except Exception as e:
        print(f"Erro ao gerar arquivo: {e}")

# Defina aqui quantos alunos você quer gerar
gerar_alunos(100)