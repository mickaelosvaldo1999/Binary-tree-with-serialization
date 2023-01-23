#include <iostream>
#include <clocale>
#include "serialCurrency.h"
#include "intserial.h"
#include "serialCurrency.h"
#include <tree.h>
#define minDegree 3

using namespace std;

int main() {
   //Setando local e variáveis iniciais.
   setlocale(LC_ALL, "Portuguese");
   int op, n;
   string chat;
   //applet de testes;
   vector<string> inserter = {"5.50","2.01", "-5.33", "10.05", "21.13", "1.88", "-3.14", "2.86", "37.55", "2.99", "34.31", "49.00", "38.26", "20.85", "23.02", "17.01", "14.92", "13.81", "39.89", "-13.22", "7.20"};
   vector<string> remover = {"5.50", "-5.33", "21.13", "1.88", "-3.14", "34.31", "38.26", "23.02", "14.92", "39.89", "7.20"};
   //Criando árvore

   tree<serialCurrency> arvore(minDegree);

   if (arvore.isOpen()) {
      cout << "Arquivo aberto com sucesso!\n\n";

      do {
         cout << "Selecione uma opção:\n\n"
              << "1. Inserir um registro\n"
              << "2. Excluir um registro\n"
              << "3. Pesquisar um registro\n"
              << "4. Printar árvore\n"
              << "5. Realizar testes\n"
              << "6. Sair\n\n"
              << "Sua opção: ";
         cin >> op;
         switch (op) {
            case 1:
               cout << "Digite um número monetário: ";
                cin >> chat;
               if (arvore.insert(chat)) {
                    cout << "Valor " << chat << " inserido com sucesso.\n" << endl;
                    arvore.print();
               }
               break;

            case 2:
               cout << "Digite valor deseja remover do arquivo: ";
               cin >> chat;
               if (arvore.remove(chat)) {
                    cout << "Valor " << chat << " removido do arquivo\n" << endl;
                    arvore.print();
               } else {
                    cout << "Valor " << chat << " não encontrado no arquivo\n" << endl;
               }
               break;

            case 3:
               cout << "Digite o valor a ser pesquisado: ";
               cin >> chat;
               bool aux;
               aux = arvore.search(chat);
               if (aux)
                  cout << "Valor " << chat << " encontrado no registro " << endl;
               else
                  cout << "Valor " << chat << " não encontrado.\n" << endl;

               break;

            case 4:
               cout << "Listando todos os registros válidos do arquivo: " << endl;
               arvore.print();
               break;

            case 5:
                cout << endl << "################################################################################" << endl;
                cout << "#                       APPLET DE TESTES                                       #" << endl;
                cout << "################################################################################" << endl;
                for (auto i : inserter) {
                    if (arvore.insert(i)) {
                        cout << "Inserindo: " << i << endl;
                        arvore.print();
                    }
                }
                break;
            case 6:
               cout << "Encerrando o programa... ";
               arvore.close();
;               cout << "concluído." << endl;
               return 0;
               break;
            default:
               cout << "Opção inválida! Tente novamente..." << endl;
               break;
         }
      } while (true);
   } else {
      cout << "Não foi possível abrir o arquivo!" << endl;
      return 1;
   }
   return 0;
}
