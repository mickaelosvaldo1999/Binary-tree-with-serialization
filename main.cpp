#include <iostream>
#include <clocale>
#include "header.h"
#include "record.h"
#include "typedfile.h"
#include "intserial.h"
#include <tree.h>
#include <node.h>
#define minDegree 3

using namespace std;

int main() {
   //Setando local e variáveis iniciais.
   setlocale(LC_ALL, "Portuguese");
   int op, n, i;
   tree<intSerial> arvore(minDegree);
   node<intSerial> test;
   test.appendValue(10);
   test.appendValue(20);
   test.appendValue(30);
   test.appendChild(8);
   node<intSerial> teste;
   teste.fromString(test.toString());
   //Iniciando objeto arquivo e verificando se é válido
   typedFile<node<intSerial>> arq("teste.dat", "BTR", 1);
   //Criando um encapsulador de registro
    record<node<intSerial>> r;
    r.setData(test);
    //TESTE

   if (arq.isOpen()) {
      cout << "Arquivo aberto com sucesso!\n\n";

      do {
         cout << "Selecione uma opção:\n\n"
              << "1. Inserir um registro\n"
              << "2. Excluir um registro\n"
              << "3. Pesquisar um registro\n"
              << "4. Printar árvore\n"
              << "5. Sair\n\n"
              << "Sua opção: ";
         cin >> op;
         switch (op) {
            case 1:
               cout << "Digite um número inteiro: ";
                cin >> n;
               if (arvore.insert(n)) {
                    cout << "Valor " << n << " inserido com sucesso.\n" << endl;
                    arvore.print();
               }
               break;
            case 2:
               cout << "Digite valor deseja remover do arquivo: ";
               cin >> n;
               //i = arq.search(teste);
               i = 0;
               if (i != 0) {
                  if (arq.deleteRecord(i))
                     cout << "Valor " << n << " removido do arquivo.\n" << endl;
                     cout << "FirstValidMain " << arq.getFirstValid() << " --" << endl;
                     //arq.clear();
               } else {
                  cout << "Valor " << n << " não encontrado no arquivo\n" << endl;
               }
               break;
            case 3:
               cout << "Digite o valor a ser pesquisado: ";
               cin >> n;
               bool aux;
               aux = arvore.search(n);
               if (aux)
                  cout << "Valor " << n << " encontrado no registro " << endl;
               else
                  cout << "Valor " << n << " não encontrado.\n" << endl;

               break;
            case 4:
               cout << "Listando todos os registros válidos do arquivo: " << endl;
               arvore.print();

               break;
            case 5:
               cout << "Encerrando o programa... ";
               arq.close();
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
