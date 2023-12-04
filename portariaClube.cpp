#include <iostream>
#include <fstream>
#include <string>

const int MAX_SOCIOS = 5;

struct Socio {
    int numeroTitulo;
    std::string nomeTitular;
    std::string nomeDependente1;
    std::string nomeDependente2;
    bool mensalidadeEmDia;
};

struct RegistroPortaria {
    int numeroTitulo;
    std::string nome;
    bool entrada;
};

struct ListaSocios {
    Socio socios[MAX_SOCIOS];
    int numSocios;
};

struct FilaPortaria {
    RegistroPortaria registros[MAX_SOCIOS];
    int frente, fundo;
};

void inicializarListaSocios(ListaSocios& lista) {
    lista.numSocios = 0;
}

void inserirSocio(ListaSocios& lista, const Socio& novoSocio) {
    if (lista.numSocios < MAX_SOCIOS) {
        lista.socios[lista.numSocios++] = novoSocio;
    } else {
        std::cout << "Capacidade máxima de sócios atingida." << std::endl;
    }
}

void listarSocios(const ListaSocios& lista) {
    for (int i = 0; i < lista.numSocios; ++i) {
        std::cout << "Número do Título: " << lista.socios[i].numeroTitulo << "\tNome do Titular: " << lista.socios[i].nomeTitular << std::endl;
    }
}

void removerSocio(ListaSocios& lista, int numeroTitulo) {
    int index = -1;
    for (int i = 0; i < lista.numSocios; ++i) {
        if (lista.socios[i].numeroTitulo == numeroTitulo) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        for (int i = index; i < lista.numSocios - 1; ++i) {
            lista.socios[i] = lista.socios[i + 1];
        }
        --lista.numSocios;
        std::cout << "Sócio removido com sucesso." << std::endl;
    } else {
        std::cout << "Sócio não encontrado." << std::endl;
    }
}

void inicializarFilaPortaria(FilaPortaria& fila) {
    fila.frente = fila.fundo = 0;
}

void enfileirar(FilaPortaria& fila, const RegistroPortaria& registro) {
    if ((fila.fundo + 1) % MAX_SOCIOS != fila.frente) {
        fila.registros[fila.fundo] = registro;
        fila.fundo = (fila.fundo + 1) % MAX_SOCIOS;
    } else {
        std::cout << "A fila está cheia." << std::endl;
    }
}

void inicializarSocios(ListaSocios& lista) {
    Socio socio1 = {1001, "Solange", "Lucas", "Renan", true};
    Socio socio2 = {1002, "Maria", "Luana", "Davi", true};
    Socio socio3 = {1003, "Carlos", "Maria", "Marcos", false};

    inserirSocio(lista, socio1);
    inserirSocio(lista, socio2);
    inserirSocio(lista, socio3);
}

int main() {
    ListaSocios listaSocios;
    FilaPortaria filaPortaria;

    inicializarListaSocios(listaSocios);
    inicializarFilaPortaria(filaPortaria);
    inicializarSocios(listaSocios);

    int opcao;
    do {
        std::cout << "\nMenu:\n1. Listar Sócios\n2. Remover Sócio\n3. Processar Portaria\n4. Gerar Relatório\n0. Sair\nEscolha uma opção: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                listarSocios(listaSocios);
                break;
            case 2: {
                int numeroTitulo;
                std::cout << "Digite o número do título do sócio a ser removido: ";
                std::cin >> numeroTitulo;
                removerSocio(listaSocios, numeroTitulo);
                break;
            }
            case 3: {
                Socio novoSocio;
                std::cout << "Número do Título: ";
                std::cin >> novoSocio.numeroTitulo;
                std::cout << "Nome do Titular: ";
                std::cin >> novoSocio.nomeTitular;
                std::cout << "Nome do Dependente 1: ";
                std::cin >> novoSocio.nomeDependente1;
                std::cout << "Nome do Dependente 2: ";
                std::cin >> novoSocio.nomeDependente2;
                std::cout << "Mensalidade em Dia (1 para Sim, 0 para Não): ";
                std::cin >> novoSocio.mensalidadeEmDia;

                inserirSocio(listaSocios, novoSocio);

                RegistroPortaria registro;
                registro.numeroTitulo = novoSocio.numeroTitulo;
                registro.nome = novoSocio.nomeTitular;

                char opcao;
                std::cout << "Entrada ou saída (E/S): ";
                std::cin >> opcao;

                registro.entrada = (opcao == 'E' || opcao == 'e');

                enfileirar(filaPortaria, registro);
                std::cout << "Registro realizado com sucesso." << std::endl;
                break;
            }
            case 4:
                break;
        }
    } while (opcao != 0);

    return 0;
}
