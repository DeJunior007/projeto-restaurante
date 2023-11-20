#include <iostream>
#include <vector>
#include <string>

struct Prato {
    std::string nome;
    std::string descricao;
    float avaliacao;
    float preco;
};

struct Restaurante {
    std::string nome;
    float avaliacao;
    std::string faixa_preco;
    std::vector<Prato> pratos;
};

struct TiposDeComida {
    std::vector<Restaurante> Churrascaria;
    std::vector<Restaurante> Pizza;
    std::vector<Restaurante> Sushi;
};

void mostrarTiposDeComida() {
    std::cout << "Tipos de Comida Disponiveis:" << std::endl;
    std::cout << "1. Churrascaria" << std::endl;
    std::cout << "2. Pizza" << std::endl;
    std::cout << "3. Sushi" << std::endl;
}

void mostrarRestaurantes(const std::vector<Restaurante>& restaurantes) {
    std::cout << "Restaurantes Disponiveis:" << std::endl;
    for (size_t i = 0; i < restaurantes.size(); ++i) {
        std::cout << i + 1 << ". " << restaurantes[i].nome << " - Avaliacao: " << restaurantes[i].avaliacao << " - Faixa de Preco: " << restaurantes[i].faixa_preco << std::endl;
    }
}

float calcularPrecoMedio(const std::vector<Prato>& pratos) {
    if (pratos.empty()) {
        return 0.0;
    }

    float somaPrecos = 0.0;
    for (const auto& prato : pratos) {
        somaPrecos += prato.preco;
    }

    return somaPrecos / pratos.size();
}

void mostrarPratos(const std::vector<Prato>& pratos) {
    std::cout << "Pratos Disponiveis:" << std::endl;
    for (size_t i = 0; i < pratos.size(); ++i) {
        std::cout << i + 1 << ". " << pratos[i].nome << " - Descricao: " << pratos[i].descricao << " - Avaliacao: " << pratos[i].avaliacao << " - Preco: " << pratos[i].preco << std::endl;
    }
}

int main() {
    std::locale::global(std::locale(""));

    TiposDeComida tiposDeComida;

    tiposDeComida.Churrascaria = {
            {"Churrascaria do Ze", 4.5, "$$$", {
                                                       {"Picanha", "Corte de carne bovina macia e suculenta.", 4.8, 30.0},
                                                       {"Costela", "Costela bovina assada lentamente.", 4.2, 25.0}
                                               }},
            {"Churrascaria da Maria", 4.2, "$$$", {
                                                       {"Picanha com Alho", "Picanha grelhada com alho.", 4.5, 32.0},
                                                       {"Linguica Toscana", "Linguica defumada com temperos italianos.", 4.0, 28.0}
                                               }}
    };

    tiposDeComida.Pizza = {
            {"Pizzaria Bella", 4.6, "$$", {
                                                  {"Pizza Margherita", "Pizza classica com molho de tomate, mucarela e manjericao.", 4.8, 20.0},
                                                  {"Pizza Pepperoni", "Pizza com pepperoni e queijo.", 4.5, 22.0}
                                          }},
            {"Pizzaria Express", 4.3, "$", {
                                                  {"Pizza Quatro Queijos", "Pizza com quatro tipos diferentes de queijo.", 4.2, 18.0},
                                                  {"Calzone", "Massa de pizza recheada com queijo, presunto e tomate.", 4.0, 15.0}
                                          }}
    };

    tiposDeComida.Sushi = {
            {"Sushi House", 4.7, "$$$$", {
                                                 {"Sashimi Misto", "Selecao de fatias finas de peixe cru.", 4.8, 35.0},
                                                 {"Temaki de Salmon", "Cone de alga recheado com arroz, salmon e outros ingredientes.", 4.6, 30.0}
                                         }},
            {"Sushi Garden", 4.5, "$$$", {
                                                 {"Nigiri de Atum", "Bolinho de arroz coberto com fatia de atum.", 4.7, 28.0},
                                                 {"Miso Soup", "Sopa a base de misso, tofu, algas e cebolinha.", 4.2, 10.0}
                                         }}
    };

    int escolhaTipoComida;
    std::cout << "Bem-vindo ao AiTome - Sistema de Selecao de Restaurantes!" << std::endl;

    std::vector<std::string> pratosEscolhidos;
    float precoTotal = 0.0;

    do {
        mostrarTiposDeComida();
        std::cout << "\nEscolha o tipo de comida (1-3, 0 para sair): ";
        std::cin >> escolhaTipoComida;

        if (escolhaTipoComida >= 1 && escolhaTipoComida <= 3) {
            const std::vector<Restaurante>& restaurantes = [&]() {
                switch (escolhaTipoComida) {
                    case 1:
                        return tiposDeComida.Churrascaria;
                    case 2:
                        return tiposDeComida.Pizza;
                    case 3:
                        return tiposDeComida.Sushi;
                    default:
                        return tiposDeComida.Churrascaria;
                }
            }();

            mostrarRestaurantes(restaurantes);

            int escolhaRestaurante;
            std::cout << "\nEscolha um restaurante (1-" << restaurantes.size() << ", 0 para voltar): ";
            std::cin >> escolhaRestaurante;

            if (escolhaRestaurante >= 1 && escolhaRestaurante <= restaurantes.size()) {
                const Restaurante& restauranteEscolhido = restaurantes[escolhaRestaurante - 1];
                std::cout << "\nRestaurante escolhido: " << restauranteEscolhido.nome << std::endl;
                std::cout << "Avaliacao: " << restauranteEscolhido.avaliacao << " - Faixa de Preco: " << restauranteEscolhido.faixa_preco << std::endl;

                int escolhaPrato;
                do {
                    mostrarPratos(restauranteEscolhido.pratos);
                    std::cout << "\nEscolha um prato (1-" << restauranteEscolhido.pratos.size() << ", 0 para finalizar): ";
                    std::cin >> escolhaPrato;

                    if (escolhaPrato >= 1 && escolhaPrato <= restauranteEscolhido.pratos.size()) {
                        const Prato& pratoEscolhido = restauranteEscolhido.pratos[escolhaPrato - 1];
                        std::cout << "\nPrato escolhido: " << pratoEscolhido.nome << std::endl;
                        pratosEscolhidos.push_back(pratoEscolhido.nome);
                        precoTotal += pratoEscolhido.preco;

                        int escolhaContinuar;
                        std::cout << "\nQuer adicionar mais algum prato desse restaurante?" << std::endl;
                        std::cout << "1. Sim" << std::endl;
                        std::cout << "2. Nao" << std::endl;
                        std::cin >> escolhaContinuar;

                        if (escolhaContinuar != 1) {
                            break;
                        }
                    } else if (escolhaPrato != 0) {
                        std::cout << "Opcao invalida. Tente novamente." << std::endl;
                    }
                } while (escolhaPrato != 0);
            } else if (escolhaRestaurante != 0) {
                std::cout << "Opcao invalida. Tente novamente." << std::endl;
            }
        } else if (escolhaTipoComida != 0) {
            std::cout << "Opcao invalida. Tente novamente." << std::endl;
        }

        if (escolhaTipoComida != 0) {
            std::cout << "\nPratos escolhidos:" << std::endl;
            for (const auto& prato : pratosEscolhidos) {
                std::cout << "- " << prato << std::endl;
            }

            std::cout << "\nPreco total: " << precoTotal << std::endl;

            int escolhaContinuar;
            std::cout << "\nEscolha uma opcao:" << std::endl;
            std::cout << "1. Continuar comprando" << std::endl;
            std::cout << "2. Finalizar compra" << std::endl;
            std::cin >> escolhaContinuar;

            if (escolhaContinuar == 2) {
                break;
            } else if (escolhaContinuar != 1) {
                std::cout << "Opcao invalida. Finalizando compra." << std::endl;
                break;
            }
        }

    } while (escolhaTipoComida != 0);

    std::cout << "\nPratos escolhidos:" << std::endl;
    for (const auto& prato : pratosEscolhidos) {
        std::cout << "- " << prato << std::endl;
    }

    std::cout << "\nPreco total: " << precoTotal << std::endl;
    std::cout << "\nObrigado por usar o AiTome - Sistema de Selecao de Restaurantes!\n\nCreditos: Deilton Pedro Jr - Platina no LOL" << std::endl;

    return 0;
}
