#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::string;
using std::vector;
using std::find;
using std::cout;
using std::cin;
using std::endl;

// Classe Marca
class Marca {
private:
    string nome;

public:
    Marca(const string& nome) : nome(nome) {}
    ~Marca() {}
    const string& get_nome() const { return nome; }
    void set_nome(const string& nome) { this->nome = nome; }
};

// Classe abstrata de Roupas
class Roupa {
protected:
    int id;
    string tipo;
    vector<Marca*> marcas;
    string tamanho;

public:
    Roupa(int id, const string& tipo, const string& tamanho) : id(id), tipo(tipo), tamanho(tamanho) {}
    virtual ~Roupa() {
        for (auto marca : marcas) {
            delete marca;
        }
    }
    const string& get_tipo() const { return tipo; }
    void set_tipo(const string& tipo) { this->tipo = tipo; }
    const vector<Marca*>& get_marcas() const { return marcas; }
    void set_marcas(const vector<Marca*>& marcas) { this->marcas = marcas; }
    const string& get_tamanho() const { return tamanho; }
    void set_tamanho(const string& tamanho) { this->tamanho = tamanho; }
    int getId() const { return id; }
    void setId(int id) { this->id = id; }

    Roupa& operator+(Marca* marcaPtr) {
        marcas.push_back(marcaPtr);
        return *this;
    }

    Roupa& operator-(Marca* marcaPtr) {
        auto it = find(marcas.begin(), marcas.end(), marcaPtr);
        if (it!= marcas.end()) {
            marcas.erase(it);
        }
        return *this;
    }

friend class Loja;
};

// Classes RoupaAdulta e RoupaInfantil
class RoupaAdulta : public Roupa {
private:
    string tipoTecido;

public:
    RoupaAdulta(int id, const string& tipo, const string& tamanho, const string& tipoTecido): Roupa(id, tipo, tamanho), tipoTecido(tipoTecido) {}
    ~RoupaAdulta() override {}
    const string& get_tipoTecido() const { return tipoTecido; }
    void set_tipoTecido(const string& tipoTecido) { this->tipoTecido = tipoTecido; }
};

class RoupaInfantil : public Roupa {
private:
    string faixaEtaria;

public:
    RoupaInfantil(int id, const string& tipo, const string& tamanho, const string& faixaEtaria): Roupa(id, tipo, tamanho), faixaEtaria(faixaEtaria) {}
    ~RoupaInfantil() override {}
    const string& get_faixaEtaria() const { return faixaEtaria; }
    void set_faixaEtaria(const string& faixaEtaria) { this->faixaEtaria = faixaEtaria; }
};

// Classe Loja
class Loja {
private:
    vector<Roupa*> roupas;

public:
   Loja() {}
   ~Loja() {
        for (auto roupa : roupas) {
            delete roupa;
        }
    }
   void adicionar_roupa(Roupa* roupa) { roupas.push_back(roupa); }

   void remover_roupa(int id) {
    auto it = find_if(roupas.begin(), roupas.end(), [id](Roupa* roupa) { return roupa->id == id; });
    if (it!= roupas.end()) {
        delete *it;
        roupas.erase(it);
    }
}

   void operator+=(Roupa* r) {
        adicionar_roupa(r);
    }

   void operator-=(Roupa* r) {
        adicionar_roupa(r);
    }

   vector<Roupa*>& get_roupas() { return roupas; }
    
};

int main() {
    // Cria uma loja de roupas
    Loja loja;
    
    // Lista de marcas, tipos de roupas e tamanhos
    vector<string> marcas;
    vector<string> tiposRoupas = {"Adulto", "Infantil"};
    vector<string> tamanhos = {"P", "M", "G", "GG"};

    // Boas-vindas ao usuário
    cout << "Bem-vindo a Beedu Beauty!\n";

    // Loop para manter o programa rodando
    while (true) {
        // Mostra o menu de opções
        cout << "\nMenu:\n";
        cout << "1. Adicionar roupa\n";
        cout << "2. Remover roupa\n";
        cout << "3. Exibir roupas\n";
        cout << "4. Sair\n";
        cout << "Escolha uma opcao: ";
        
        // Lê a opção escolhida pelo usuário
        int opcao;
        cin >> opcao;

        // Processa a opção escolhida
        switch (opcao) {
            case 1: {
                // Pede ao usuário informações para criar uma nova roupa
                string tipo, tamanho, tipoTecido, faixaEtaria;
                int id;
                cout << "ID da roupa: ";
                cin >> id;
                cout << "Tipo de roupa (Adulto/Infantil): ";
                cin >> tipo;
                cout << "Tamanho (P/M/G/GG): ";
                cin >> tamanho;
                
                // Dependendo do tipo de roupa, pega mais informações
                if (tipo == "Adulto") {
                    cout << "Tipo de tecido: ";
                    cin >> tipoTecido;
                    // Cria uma nova roupa adulta e adiciona à loja
                    RoupaAdulta* roupaAdulta = new RoupaAdulta(id, tipo, tamanho, tipoTecido);
                    loja.adicionar_roupa(roupaAdulta);
                } else if (tipo == "Infantil") {
                    cout << "Faixa etaria: ";
                    cin >> faixaEtaria;
                    // Cria uma nova roupa infantil e adiciona à loja
                    RoupaInfantil* roupaInfantil = new RoupaInfantil(id, tipo, tamanho, faixaEtaria);
                    loja.adicionar_roupa(roupaInfantil);
                }
                break;
            }
            case 2: {
                // Pede ao usuário o ID da roupa a ser removida
                int id;
                cout << "ID da roupa a ser removida: ";
                cin >> id;
                // Remove a roupa com o ID especificado da loja
                loja.remover_roupa(id);
                break;
            }
            case 3: {
                // Exibe todas as roupas armazenadas na loja
                for (const auto& roupa : loja.get_roupas()) {
                    cout << "Tipo: " << roupa->get_tipo() << ", Tamanho: " << roupa->get_tamanho();
                    if (roupa->get_tipo() == "Adulto") {
                        cout << ", Tipo de Tecido: " << ((RoupaAdulta*) roupa)->get_tipoTecido();
                    } else if (roupa->get_tipo() == "Infantil") {
                        cout << ", Faixa Etaria: " << ((RoupaInfantil*) roupa)->get_faixaEtaria();
                    }
                    cout << endl;
                }
                break;
            }
            case 4: {
                // Finaliza o programa
                cout << "Finalizando!\n";
                return 0;
            }
            default: {
                // Informa ao usuário que a opção escolhida é inválida
                cout << "Opcao invalida.\n";
                break;
            }
        }
    }

    // Retorna 0 para indicar que o programa terminou com sucesso
    return 0;
}

