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
   node<intSerial> test;
   test.appendValue(10);
   test.appendValue(20);
   test.appendValue(30);
   test.appendChild(8);

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
              << "4. Listar todos os registros\n"
              << "5. Sair\n\n"
              << "Sua opção: ";
         cin >> op;
         switch (op) {
            case 1:
               cout << "Digite um número inteiro: ";
               cin >> n;
               //r = record<node<intSerial>>(teste);

               if (arq.insertRecord(r)) {
                    cout << "Valor " << n << " inserido com sucesso.\n" << endl;
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
               //i = arq.search(teste);
               i = 0;
               if (i != 0)
                  cout << "Valor " << n << " encontrado no registro " << i << ".\n" << endl;
               else
                  cout << "Valor " << n << " não encontrado.\n" << endl;

               break;
            case 4:
               cout << "Listando todos os registros válidos do arquivo: " << endl;
               i = arq.getFirstValid();
               if (i == 0) {
                  cout << "Não existem registros no arquivo.\n" << endl;
               } else {
                  while (i != 0) {
                     //arq.readRecord(r, i);
                     cout << "- " << r.getData().print() << endl;
                     i = r.getNext();
                  }
                  cout << endl;
               }

               break;
            case 5:
               cout << "Encerrando o programa... ";
               arq.close();
               cout << "concluído." << endl;
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
