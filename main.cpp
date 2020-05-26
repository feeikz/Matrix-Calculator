#include "main.h"

/**
 * @brief Program na vypocet matic, korenov a determinantu matic.
 * @file main.cpp
 * @author Frederik Zajac
 * @mainpage LOGIN ZAJ0098 - Maticove operacie
 */



/**
 *
 * @brief Funkcia sluzi na vypis matice do konzole.
 *
 * @param matica - ukazatel na dynamicky alokovane dvojrozmerne pole.
 * @param n - pocet raidkov matice
 * @param m - pocet prvkov matice
 */

void vypis(double**matica,int n,int m)
{
    //cout << "vypisana matica" << endl;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                cout <<fixed<<setprecision(3)<< matica[i][j] << "\t";
            }
            cout << endl;
        }
}
/**
 *
 * @brief Funkcia sluzi na vypis a vypocet determinantu.
 *
 * @param matica - ukazatel na dynamicky alokovane dvojrozmerne pole.
 * @param n - pocet riadkov matice
 * @param m - pocet prvkov matice
 * @return vracia vysledok determinantu
 */


double determinant (double **&matica, int n, int m)
{
    double vysledok = 1;

      for(int i = 0; i < n; i++)
   {
        for(int j = 0; j < m; j++)
        {
            if (i == j)
            vysledok *= matica[i][j];
        }
   }
return vysledok;
}


/**
 *
 * @brief Funkcia sluzi na vypocet korenov matice.
 *
 * @param A - ukazatel na dynamicky alokovane dvojrozmerne pole.
 * @param n - pocet riadkov matice
 * @param m - pocet prvkov matice
 * @return vracia vysledok korenov
 */
double* korene (double **A,int n, int m)
{
double* x = new double [n];

          for (int i = n-1; i >= 0; i--)
            {
                x[i] = A[i][n];
                for (int j = i+1; j < n; j++)
                   {
                        if (j!=i)
                        x[i] = x[i] - A[i][j] * x[j];
                   }

                x[i] = x[i] / A[i][i];
            }

return x;
}

/**
 *
 * @brief Funkcia sluzi na najdenie prveho nenuloveho prvku v riadku.
 *
 * @param riadok - ukazatel na dynamicky alokovane jednorozmerne pole.
 * @param m - pocet prvkov matice.
 * @return vracia hodnotu preveho nenuloveho prvku.
 */
int prvyNenulovy(double* riadok,int m)
{
    for(int i = 0 ;i < m; i++)
    {
        if(riadok[i]!=0)
        {
            //cout<<i<<"="<<endl;
            return i;
        }
    }
    //cout<<m<<"="<<endl;
    return m;
}

/**
 *
 * @brief Funkcia sluzi na vymenu riadkov podla pravidiel Gaussovej eliminačnej metody.
 *
 * @param A - ukazatel na hodnotu dynamicky alokovaneho dvojrozmerneho pola.
 * @param n - pocet riadkov matice.
 * @param m - pocet prvkov matice.
 */
void vymenaRiadkov(double**&A,int n,int m)
{
 //cout<<n<<" "<<m<<endl;
    for (int i = 0; i < n; i++)
    {
        for (int k = i + 1;k < n;k++)
        {
            //cout<<abs(A[i][i])<<" vs " << abs(A[k][i])<<endl;

            if (prvyNenulovy(A[i],m)>prvyNenulovy(A[k],m))
            {
                for (int j = 0 ;j < m; j++)
                {
                    double temp = A[i][j];
                    A[i][j] = A[k][j];
                    A[k][j] = temp;
                }
            }
            //cout<<"______________________"<<i<<"________"<<k<<endl;
            //vypis(A,n,m);
        }

    }
}
/**
 *
 * @brief Pouzije se Gaussova eliminacna metoda
 * @param A - ukazatel na hodnotu dynamicke alokovaneho dvojrozmerneho pola
 * @param n - pocet riadkov matice
 * @param m - pocet prvkov matice
 */

double** GaussovaMetoda(double **matica, int n, int m)
{
double** A = new double*[n];
for(int i = 0;i<n;i++)
{
    A[i]=new double[m];
    for(int j = 0;j<m;j++)
    {
        A[i][j]=matica[i][j];
    }
}
      //double *temp = new double[n];


  vymenaRiadkov(A,n,m);


//vykonanie gaussovej eliminacie
    for (int i = 0; i < m; i++)
    {
        int k;
        for (  k = i + 1; k < n; k++)
            {
                double t = A[k][prvyNenulovy(A[k],m)] / A[i][prvyNenulovy(A[k],m)];

                    for (int j = 0;j < m; j++)
                    {
                          A[k][j] = A[k][j] - t*A[i][j];    //nastavy prvky pod pivotnými prvkami na nulu
                          A[k][j]=abs(A[k][j])<0.001?0:A[k][j];
                    }

            }
            vymenaRiadkov(A,n,m);
            if(prvyNenulovy(A[k-1],m)>=k-1)
            {
                break;
            }
            cout<<"_________________________________"<<endl;
    }
return A;

}

/**
 *
 *
 * @brief Nacitanie matice z konzole
 *
 * @param A - ukazatel na hodnotu dynamicke alokovaneho dvojrozmerneho pola
 * @param n - pocet radkov matice
 * @param m - pocet prvkov matice
 */
void inic(double **&matica, int n,int m)
{
    int prvky;

	cout  << "Spracovane. Vlozte prvky."<<endl;
	for (int i = 0; i < n; i++)
	{

		for (int j = 0; j < m; j++)
		{
			cin >> prvky;
			if (cin.fail())
			{
				cout << "Zle zadanie prvkov" << endl;
				exit(0);
			}
			matica[i][j] = prvky;
		}
	}
	cout << endl;
}

/**
 *
 * @brief Funkcia zisti pocet riadkov suboru.
 *
 * @param string - nazov suboru
 * @return vracia pocet riadkov
 */

int xSuborRiadky(string meno)
{

    ifstream subor;
    subor.open(meno.c_str());

    if (!subor.is_open())
      {
       cout <<"Chyba pri otvarani suboru"<<endl;
       return 0;
      }

    string a;
    int i = 0;
    while(getline(subor,a,'\n'))
      {
        i++;
      }

    //int n = riadky(i);
    subor.close();
    return i;
}

/**
 *
 *
 * @brief Funkcia zisti pocet stlpcov suboru.
 *
 * @param string - nazov suboru.
 * @return vracia pocet stlpcov.
 */
int xSuborStlpce(string meno)
{
    ifstream subor;
    subor.open(meno.c_str());

    if (!subor.is_open())
    {
        cout <<"Chyba pri otvarani suboru"<<endl;
        return 0;
    }
    string help;
    getline(subor,help,'\n');
    stringstream pamet(help);
    string a;
    int i = 0;
    while(pamet >> a)
      {
        i++;
      }
    subor.close();
    return i;
}

/**
 *
 *
 * @brief Nacitanie matice zo suboru.
 *
 * @param matica - ukazatel na dynamicky alokovane dvojrozmerne pole.
 * @param n - pocet radkov matice
 * @param m - pocet prvkov matice
 * @param string - nazov suboru.
 */

void inicSubor(double **matica, int n,int m,string meno)
{
	ifstream subor;
	subor.open(meno.c_str());
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			subor >> matica[i][j];

		}
	}
	cout << endl;
	subor.close();
}
/**
 *
 *
 * @brief Funkcia zistuje pocet riadkov matice zo vstupu z konzoly.
 *
 * @return Vracia pocet radkov.
 */

int xRucneRiadky()
{
        cout <<"Zadajte pocet riadkov:"<<endl;
        int n;
        cin >> n;
        if (cin.fail() || n < 1)
            {
                cout <<"CHYBA!"<<endl;
                exit(0);
            }
    return n;
}

/**
 *
 *
 * @brief Funkcia zistuje pocet prvkov matice zo vstupu z konzoly.
 *
 * @return Vracia pocet prvkov.
 */
int xRucnePrvky()
{
        cout <<"Zadajte pocet prvkov:"<<endl;
        int m;
        cin >> m;
        if (cin.fail() || m < 1)
            {
                cout <<"CHYBA!"<<endl;
                exit(0);
            }
        return m;
}

/**
 *
 *
 * @brief Funkcia vypise vysledok v HTML.
 * @param A - ukazatel na dynamicke alokovane dvourozmerne pole
 * @param n - pocet riadkov matice
 *
 */
void HTMLvystup(double **matica,double** gauss, int n,int m)
{
    cout << "Zadajte meno suboru HTML: ";
 string meno_subor;
 cin >> meno_subor;
 meno_subor = meno_subor + ".html";

 string hlavicka =
  "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">"
  "<META http-equiv=Content-Type content=\"text/html; charset=windows-1250\">"
  "<HTML>"
  "<head> <title>Matice</title>"
  "</head>"
  "<body>";
  string zaciatok_tabulky=  "<table width=100>";
 string koniec_tabulky= "</table>";string paticka="</body></html>";

 ofstream vystup_HTML(meno_subor.c_str());

 if (vystup_HTML.fail())
{
    cout <<"Nepodarilo se otvorit vystup."<<endl;
    exit(0);
 }
 vystup_HTML << hlavicka;
 vystup_HTML<<zaciatok_tabulky;
 for (int i = 0; i < n; i++)
    {
        vystup_HTML <<"<tr>";
        for (int j = 0; j < m; j++)
        {
            vystup_HTML <<"<td>"<<setprecision(3)<<fixed<< matica[i][j]<<"</td>";
            if (j == n-1)
            {
                vystup_HTML << "<td>|</td>";
            }
        }
        vystup_HTML<<"</tr>";
    }
    vystup_HTML << koniec_tabulky;
vystup_HTML<<"Matica po Gaussovej eliminaci:<br />";
   vystup_HTML<<zaciatok_tabulky;
 for (int i = 0; i < n; i++)
    {
        vystup_HTML <<"<tr>";
        for (int j = 0; j < m; j++)
        {
            vystup_HTML <<"<td>"<<setprecision(3)<<fixed<< gauss[i][j]<<"</td>";
            if (j == n-1)
            {
                vystup_HTML << "<td>|</td>";
            }
        }
        vystup_HTML<<"</tr>";
    }
    vystup_HTML << koniec_tabulky;

     if (n != m-1)
           {
               vystup_HTML<<"Hodnoty premennych sa nedaju vypocitat.<br />"<<endl;
           }

           else
           {
                double sucin = 1;
                for(int i =0;i<n;i++)
                    {
                        sucin*=gauss[i][i];
                        if(sucin==0)
                        {
                            break;
                        }
                    }

              if(sucin==0)
                {
                    vystup_HTML<<"Existuje nekonecne vela korenov.<br /> "<<endl;
                }

                else
                {
                    double* x = korene(gauss,n,m);
                    vystup_HTML<<"Hodnoty korenov su:<br /> "<<endl;
                    for (int i = 0; i < n; i++)
                    {
                        vystup_HTML<<x[i]<<"<br />"<<endl;
                    }

                }

           }

        if ( n != m)
        {
             vystup_HTML<<"Determinant sa neda vypocitat.<br />"<<endl;
        }
        else
        {
            vystup_HTML<<"Determinant je: "<<determinant(gauss,n,m)<<endl;
        }





    vystup_HTML<<paticka;


 vystup_HTML.close();

}


/**
 *
 *
 * @brief Funkcia sa spyta, ci chceme vysledok zapisat do HTML.
 * @param matica - ukazatel na dynamicke alokovane dvourozmerne pole
 * @param n - pocet riadkov matice
 * @return Vracia vyber uzivatela.
 */
int html()
{
    int dotaz;
    cout <<"Prajete si vypisat vyslednu maticu do html suboru?"<<endl<<"0 - Nie"<<endl<<"1 - Ano"<<endl;
    cin >> dotaz;
    if (cin.fail() || dotaz > 1)
    {
        cout <<"Zle zadane."<<endl;

        exit(0);
    }

    return dotaz;

}


/**
 * @fn int main()
 *
 * @brief Hlavna funkcia programu. Pyta sa, akym spsosobom chceme zadat maticu a nasledne vola prislusne funkcie.
 * @return Vracia nulu a ukončí program.
 */
int main()
{
     int vstup, n,m;
double **matica;
 cout <<"Definujte maticu."<<endl<<"0 - rucne"<<endl<<"1 - zo suboru"<<endl;
 cin >> vstup;


    if (vstup == 0)
    {
        n = xRucneRiadky();
        m = xRucnePrvky();



        matica = new double*[n];
        for (int i = 0; i < n; i++)
        {
            matica[i] = new double[m];
        }
        inic(matica, n,m);



    }

    else if (vstup == 1)
    {
  string meno;
        cout<<"Zadajte cestu k suboru"<<endl;
        cin >> meno;
        n = xSuborRiadky(meno.c_str());
        m = xSuborStlpce(meno.c_str());

        matica = new double*[n];
        for (int i = 0; i < n; i++)
        {
            matica[i] = new double[m];

        }

       inicSubor(matica, n,m,meno);

    }

    else if ((vstup != 0) || (vstup !=1))
    {
        cout << "Zle zadanie. Koniec programu"<<endl;
        return 0;
    }

        cout<<"****Zadana matica:  ******"<<endl;
        vypis(matica,n,m);
        double** gaussovamatica = GaussovaMetoda(matica,n, m);
        cout<<"****Matica po Gaussovej eliminaci je:  ******"<<endl;
        vypis(gaussovamatica,n,m);


          if (n != m-1)
           {
               cout<<"Hodnoty premennych sa nedaju vypocitat."<<endl;
           }

           else
           {
                double sucin = 1;
                for(int i =0;i<n;i++)
                    {
                        sucin*=gaussovamatica[i][i];
                        if(sucin==0)
                        {
                            break;
                        }
                    }

              if(sucin==0)
                {
                    cout<<"Existuje nekonecne vela korenov. "<<endl;
                }

                else
                {
                    double* x = korene(gaussovamatica,n,m);
                    cout<<"Hodnoty korenov su: "<<endl;
                    for (int i = 0; i < n; i++)
                    {
                        cout<<x[i]<<endl;
                    }

                }

           }

        if ( n != m)
        {
             cout<<"Determinant sa neda vypocitat."<<endl;
        }
        else
        {
            cout<<"Determinant je "<<determinant(gaussovamatica,n,m)<<endl;
        }
if (html())
    {
        HTMLvystup(matica,gaussovamatica, n,m);

    }



    for (int i = 0; i < n; i++)
    {
        delete [] matica[i];
    }
    delete [] matica;
    return 0;
}

