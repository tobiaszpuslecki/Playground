#include <iostream>
#define MAX_SIZE 3000



//+ - . , [ ] < >

class Brainfuck
{


	private:
		char* d;
		const char* p;

		void pincr()
		{
			d++;
		}

		void pdecr()
		{
			d--;
		}

		void bincr()
		{
			(*d)++;
		}

		void bdecr()
		{
			(*d)--;
		}

		void print()
		{
			std::cout << *d;
		}

		void read()
		{
			std::cin >> *d;
		}

		void bropen()
		{
			int bal=1;

			if(*d=='\0')
			{
				do{
					p++;
					if(*p=='[') bal++;
					else if(*p==']') bal--;
				}while(bal!=0);
			}
		}

		void brclose()
		{
			int bal=0;

			do{
				if(*p=='[') bal++;
				else if(*p==']') bal--;
				p--;
			}while(bal!=0);
		}


	public:
		char* getD()
		{
			return d;
		}


		Brainfuck(const char prog[])
		{
			p = prog;
		}

		void eval()
		{
			while(*p)
			{
				switch(*p)
				{
					case '>':
					pincr();
					break;

					case '<':
					pdecr();
					break;

					case '+':
					bincr();
					break;

					case '-':
					bdecr();
					break;

					case '.':
					print();
					break;

					case ',':
					read();
					break;

					case '[':
					bropen();
					break;

					case ']':
					brclose();
					break;

					default:
					std::cout << "ERROR";
					break;

				}

				p++;
			}
		}


};



// int main(int argc, char const *argv[]) {
// 	/* code */
// 	return 0;
// }
