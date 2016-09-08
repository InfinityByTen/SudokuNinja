// sudoku_solver.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
#include<string.h>

#define rep(i, a, b) for(int i=(a);i<(b);i++)

using namespace std;


string cand[81][9][9],box[3][3];  string::iterator it,itr[81];

char sud[81][9][9],col[9],c,sol_cpy[9][9];

int rc[9][9],cc[9][9],bc[9][9],freq[9]={0},loc[9][2];

void eval(int sel, char sud [][9][9], string cand[][9][9],int d, ofstream& op);
int check(char sud[][9][9], int d),solution_count=0;


void populate(int d)
   {for(int i=0;i<9;i++)
     for(int j=0;j<9;j++)
		 cand[d][i][j]="123456789";
   } // populates the initial candidates


void create_copy(string cand[][9][9], char sud[][9][9],int d)
   {rep(i,0,9)
      rep(j,0,9)
        {cand[d+1][i][j]= cand[d][i][j];
         sud[d+1][i][j]= sud[d][i][j];
        }
   } // when hit and trail approached, creates copies to be worked upon


void dispcand(string cand[][9][9],int d, ofstream& op)
{for(int i=0;i<9;i++)
       {for(int j=0;j<9;j++)
          {cout<<" "<<cand[d][i][j]<<" ";op<<" "<<cand[d][i][j]<<" ";
          if((j+1)%3==0) {cout<<"|";op<<"|";}
          }
        if((i+1)%3==0){cout<<"\n------------------------------\n";op<<"\n------------------------------\n";}else{ cout<<"\n";op<<"\n";}
       }
   }
//diplays the candidates- original or copy as required


void dispsud (char sud[][9][9],int d)
    {cout<<"check returned  "<<check(sud,d)<<"\n\n";
	rep(i,0,9)
      {rep(j,0,9)
         {cout<<" "<<sud[d][i][j]<<" ";
          if((j+1)%3==0) cout<<"|";
         }
       if((i+1)%3==0)cout<<"\n------------------------------\n";else cout<<"\n";
      }
    }

int elimrow(char sud[9], int r, string cand[][9][9],int d)
     {int ret=0;
      rep(i,0,9)
		 rep(j,0,9)
		 if(sud[i]!='_'&& j!=i && find(cand[d][r][j].begin(),cand[d][r][j].end(),sud[i])!=cand[d][r][j].end())
            {it=find(cand[d][r][j].begin(),cand[d][r][j].end(),sud[i]);
	         cand[d][r][j].erase(it);
	         ret=1;
	        }
	  return ret;
     }
// eliminates row from the given candidate set

int elimcol(char col[9],int cl, string cand[][9][9], int d)
     {int ret=0;
      rep(i,0,9)
		 rep(j,0,9)
	       {if(i!=j && col[i]!='_' && find(cand[d][j][cl].begin(),cand[d][j][cl].end(),col[i])!=cand[d][j][cl].end())
              {it=find(cand[d][j][cl].begin(),cand[d][j][cl].end(),col[i]);
	           cand[d][j][cl].erase(it);
			   ret=1;
	           }
	       }
	  return ret;
     }
// eliminates colums from the given candidate set


int chpair (int in , int sel, string cand[][9][9], int d)
     {int ret=0;
      int com =0;

if(sel==0)
   {while(com<9)
      {rep(i,0,9)
         {if(cand[d][in][i].length()==2 && cand[d][in][com]==cand[d][in][i] && i!=com)rep(t,0,9)
            {if(t!=i && t!=com && find(cand[d][in][t].begin(),cand[d][in][t].end(),cand[d][in][com][0])!=cand[d][in][t].end())
               {it=find(cand[d][in][t].begin(),cand[d][in][t].end(),cand[d][in][com][0]);
                cand[d][in][t].erase(it);
				ret=1;
                }        // identifies occurance of pairs in a row of a given candidate set
     	 if(t!=i && t!=com && find(cand[d][in][t].begin(),cand[d][in][t].end(),cand[d][in][com][1])!=cand[d][in][t].end())
	         {it=find(cand[d][in][t].begin(),cand[d][in][t].end(),cand[d][in][com][1]);
	          cand[d][in][t].erase(it);
		      ret=1;
	         }
            }
         }
       com++;
      }
}

if(sel==1)
{while(com<9)
     {rep(i,0,9)
        {if(cand[d][i][in].length()==2 && cand[d][com][in]==cand[d][i][in] && i!=com)
	  rep(t,0,9)
        {if(t!=i && t!=com && find(cand[d][t][in].begin(),cand[d][t][in].end(),cand[d][com][in][0])!=cand[d][t][in].end())
           {it=find(cand[d][t][in].begin(),cand[d][t][in].end(),cand[d][com][in][0]);
            cand[d][t][in].erase(it);
			ret=1;
           }        // identifies occurance of pairs in columns
	 if(t!=i && t!=com && find(cand[d][t][in].begin(),cand[d][t][in].end(),cand[d][com][in][1])!=cand[d][t][in].end())
	     {it=find(cand[d][t][in].begin(),cand[d][t][in].end(),cand[d][com][in][1]);
	     cand[d][t][in].erase(it);ret=1;
	     }
        }
        }
         com++;
      }
}

if(sel==2)
{
for(int i=0; i<9; i+=3)
	for(int j=0; j<9; j+=3)
      {rep(u,i,i+3)
	     rep(v,j,j+3)
           {if(cand[d][u][v].length()==2)
	           {rep(p,i,i+3)
			      rep(q,j,j+3)
	                  {if(!(p==u && q==v) && cand[d][p][q]==cand[d][u][v])
                           {rep(m,i,i+3)
						      rep(n,j,j+3)
	                             {if(!(m==p && n==q) && !(m==u && n==v) && find(cand[d][m][n].begin(), cand[d][m][n].end(), cand[d][u][v][0]) != cand[d][m][n].end())
	                                 {it=find(cand[d][m][n].begin(), cand[d][m][n].end(), cand[d][u][v][0]);
                                      cand[d][m][n].erase(it);
									  ret=1;
                                     }
                                  if(!(m==p && n==q) && !(m==u && n==v) && find(cand[d][m][n].begin(), cand[d][m][n].end(), cand[d][u][v][1]) != cand[d][m][n].end())
	                                 {it=find(cand[d][m][n].begin(), cand[d][m][n].end(), cand[d][u][v][1]);
								      cand[d][m][n].erase(it);
									  ret=1;
								     }
	                              }
	                       }
	                   }
	             }
	        }
	   }  // identifies occurance of pairs in boxes
}


return ret;

}


void cpy(char sud[9],int r, int d)
{rep(i,0,9)if(sud[i]!='_')cand[d][r][i]=sud[i];}          // copies given sudoku elemnts onto candidates



int check(char sud[][9][9], int d)
{int incomplete=0,flag=0;
memset(rc,0,sizeof(rc)); memset(cc,0, sizeof(cc));memset(bc,0,sizeof(bc));
rep(i,0,9)rep(j,0,9){if(sud[d][i][j]=='_')incomplete=1;}
if(incomplete==0)
{int b=0;
	rep(i,0,9)
	 rep(j,0,9)
        if(sud[d][i][j]!='_')
		   { rc[i][(int)sud[d][i][j]%48-1]++;
             cc[j][(int)sud[d][i][j]%48-1]++;
           }
 for(int i=0; i<9; i+=3)
	  for(int j=0; j<9; j+=3)												// checks sudoku in all respects. 1 for correct else 0.
        {rep(u,i,i+3)
		  rep(v,j,j+3)
		   bc[b][(int)sud[d][u][v]%48-1]++;
           b++;
	    }
int i,j,flag;
flag=1;i=0;j=0;
for(i=0;i<9 && flag==1;i++)
	for(j=0;j<9 && flag==1;j++)
	   {if(rc[i][j]!=1 || bc[i][j]!=1 || cc[i][j]!=1)flag=0;}

	if(flag==0)return 0; else return 1;
}
else return 0;
}


int contra(string cand[][9][9], int d)
{int flag =1;
for(int x=0;x<9 && flag==1;x++)
  for(int y=0;y<9 && flag==1;y++)                        // checks for null candidate in candidate copy due to wrong assumption
     {if(cand[d][x][y].length()==0) flag=0;
      rep(a,0,9)
	       {if (y!=a && cand[d][x][y].length()==1 && cand[d][x][a].length()==1 && cand[d][x][y]==cand[d][x][a])
		    flag=0;
	       }
     }
     if(flag==0)return 0; else return 1;
}


void fix(char sud[][9][9], string cand[][9][9], int d)
    {rep(i,0,9)
	   rep(j,0,9)
	     if(cand[d][i][j].length()==1)
		   {it=cand[d][i][j].begin();
             sud[d][i][j]=*it;
           }
     }


void assume(char val, int x, int y, int d)
{
cand[d][x][y]= val;
}


int elimbox(string cand[][9][9],char sud[][9][9], int d)
{ int ret=0;
   for(int i=0; i<9; i+=3)
	   for(int j=0; j<9; j+=3)
	      {rep(u,i,i+3)
		     rep(v,j,j+3)
	           { if(sud[d][u][v]!='_')
                  {rep(p,i,i+3)
				     rep(q,j,j+3)
	                    {if(!(p==u && q==v) &&find(cand[d][p][q].begin(),cand[d][p][q].end(),sud[d][u][v])!=cand[d][p][q].end() )
                           {it=find(cand[d][p][q].begin(),cand[d][p][q].end(),sud[d][u][v]);
                            cand[d][p][q].erase(it);
							ret=1;
                           }
	                    }
	              }
	           }
	      }

 return ret;
}



int freqchk(int in, int sel, string cand[][9][9], int d)
{memset(loc,-1,sizeof(loc));

int ret=0;

if(sel==2)
  {for(int i=0; i<9; i+=3)
     for(int j=0; j<9; j+=3)
	   {rep(u,i,i+3)
	     rep(v,j,j+3)
	       {it=cand[d][u][v].begin();
            while(it!=cand[d][u][v].end())
			 {if(freq[((int)(*it)%48)-1]==0)
			     {freq[((int)(*it)%48)-1]=1;
			      loc[((int)(*it)%48)-1][0]=u;
				  loc[((int)(*it)%48)-1][1]=v;
			      }
              else
			      {loc[((int)(*it)%48)-1][0]=-1;
			       loc[((int)(*it)%48)-1][1]=-1;
			       }
			  ++it;
			  }
           }
   rep(b,0,9)
      {if(loc[b][0]!=-1 && loc[b][1]!=-1 && cand[d][loc[b][0]][loc[b][1]].length()!=1 )
           {cand[d][loc[b][0]][loc[b][1]]=(char)(b+49);
            ret=1;
           }
      }
   rep(z,0,9)freq[z]=0;}//memset(loc,-1,sizeof(loc));
  }

if(sel==0)
{int index=0;
rep(u,0,9)
   {it=cand[d][in][u].begin();
   while(it!=cand[d][in][u].end())
      {if(freq[(int)(*it)%48-1]==0)
          {freq[(int)(*it)%48-1]=1;
           loc[(int)(*it)%48-1][0]=in;
		   loc[(int)(*it)%48-1][1]=u;
          }
    else
	     {loc[((int)(*it)%48)-1][0]=-1;
          loc[((int)(*it)%48)-1][1]=-1;
         }
       ++it;
       }
   }
    rep(z,0,9)freq[z]=0;
    rep(b,0,9)
	     {if(loc[b][0]!=-1 && loc[b][1]!=-1 && cand[d][loc[b][0]][loc[b][1]].length()!=1)
	         {cand[d][loc[b][0]][loc[b][1]]=(char)(b+49);
	          ret=1;
	         }
	      }
	rep(z,0,9)freq[z]=0;
//memset(loc,-1,sizeof(loc));
}

if(sel==1)
{int index=0;
rep(u,0,9)
   {it=cand[d][u][in].begin();
      while(it!=cand[d][u][in].end())
        {if(freq[(int)(*it)%48-1]==0)
	       {freq[(int)(*it)%48-1]=1;
	        loc[(int)(*it)%48-1][0]=u;
			loc[(int)(*it)%48-1][1]=in;
	       }
        else
		   {loc[((int)(*it)%48)-1][0]=-1;
	        loc[((int)(*it)%48)-1][1]=-1;
	        }
	     ++it;
	    }
   }
rep(z,0,9)freq[z]=0;
rep(b,0,9)
   {if(loc[b][0]!=-1 && loc[b][1]!=-1 && cand[d][loc[b][0]][loc[b][1]].length()!=1)
      {cand[d][loc[b][0]][loc[b][1]]=(char)(b+49);
       ret=1;
	   }
   }
rep(z,0,9)freq[z]=0;
//memset(loc,-1,sizeof(loc));
}
return ret;
}


void h_t(string cand[][9][9],char sud[][9][9], int d, ofstream& op)
{int flag=0,i=0,j=0;
while(i<=8)
	{while(j<=8)
       {if(cand[d][i][j].length()>1)
          {itr[d]=cand[d][i][j].begin();
		    for(;itr[d]!=cand[d][i][j].end() /*&& flag==0*/; itr[d]++)
			  {assume(*itr[d],i,j,d+1);
             //cout<<" assuming "<< *itr[d] <<" at "<< i +1 <<" "<<j+1 <<"\n \n";
			  fix(sud,cand,d+1);
			 //dispcand(cand, d+1);
              eval(1,sud,cand,d+1,op);
			  if(check(sud,d+1)==1){cout<<"\n\nA solution to Your Sudoku is :- \n\n"; op<<"\n\n A solution to Your Sudoku is :- \n\n";dispcand(cand ,d+1,op);++solution_count;/*std::cin.get();*/create_copy(cand,sud,d);}
			  else {create_copy(cand,sud,d); /*cout<<"There was a wrong assumption, I'll give another try \n";*/}
		      if((itr[d]+1)==cand[d][i][j].end())flag=1;
			  }
            }
			if(flag==1)break;
            ++j;
		}
         j=0;
         if(flag==1)break;
		 ++i;
       }

return;
}



int ret, ret_f;


void eval(int sel, char sud[][9][9], string cand[][9][9],int d, ofstream& op)
{
switch(sel)
{
case 1: rep(i,0,9)
		 {ret_f=elimrow(sud[d][i],i,cand, d);
	      cpy(sud[d][i],i,d);
		   if(ret_f==1)
		     {ret=1;
		      fix(sud,cand,d);
		      //dispcand(cand, d);
              //dispsud(sud, d);
		     }
		 }
	    if(contra(cand,d)==0 || check(sud,d)==1)return;
		else eval(++sel,sud ,cand,d,op);
		break;

case 2: rep(i,0,9)
		 {rep(j,0,9)
		   {col[j]=sud[d][j][i];}
		    ret_f=elimcol(col,i, cand,d);
		    if(ret_f==1)
			  {ret=1;
			   //dispcand(cand,d);
			   fix(sud,cand,d);
			   //dispsud(sud,d);
			  }
		 }
		if(contra(cand ,d)==0 || check(sud,d)==1)return;
		else eval(++sel,sud ,cand,d,op);
		break;

case 3: ret_f= elimbox(cand,sud,d);
	    if(ret_f==1)
		 { ret=1;
		   //dispcand(cand,d);
		   fix(sud,cand,d);
		   //dispsud(sud,d);
		 }
		if(contra(cand,d)==0 || check(sud,d)==1)
			return;
		else eval(++sel,sud ,cand,d,op);
		break;

case 4: ret_f= freqchk(0,2,cand,d);
	    if(ret_f==1)
		{ret=1;
		//dispcand(cand,d);
		fix(sud,cand,d);
		//dispsud(sud,d);
		}
		if(contra(cand,d)==0 || check(sud,d)==1)
			return;
		else eval(++sel,sud ,cand,d,op);
		break;

case 5: rep(m,0,9)
		 {if(contra(cand,d)==0 || check(sud,d)==1)return;
	     ret_f= freqchk(m,1,cand,d);
		 if(ret_f==1)
		   {ret=1;
		  // dispcand(cand,d);
				fix(sud,cand,d);
			//dispsud(sud,d);
		   }
		 if(contra(cand,d)==0 || check(sud,d)==1)return;
        ret_f= freqchk(m,0,cand,d);
		if(ret_f==1)
		   {ret=1;//dispcand(cand,d);
		    fix(sud,cand,d);
			//dispsud(sud,d);
		   }
		 }
		if(contra(cand,d)==0 || check(sud,d)==1)return;
		else eval(++sel,sud ,cand,d,op);
		break;

case 6: rep(m,0,9)
		{if(contra(cand,d)==0 || check(sud,d)==1)return;
	     ret_f = chpair(m,0,cand,d);
		 if(ret_f==1)
		  {ret=1;
		  fix(sud,cand,d);
		 //dispcand(cand,d);
//		 dispsud(sud,d);

		 }
		 if(contra(cand,d)==0 || check(sud,d)==1)return;
         ret_f = chpair(m,1,cand,d);
		 if(ret_f==1)
		  {ret=1;
		  fix(sud,cand,d);
		// dispcand(cand,d);
		 //dispsud(sud,d);
		  }
		}
		if(contra(cand,d)==0 && check(sud,d)==1)return;
		else eval(++sel,sud ,cand,d,op);
		break;

case 7: ret_f = chpair(0,2,cand,d);
	    if(ret_f==1)
		 {ret=1;
		 fix(sud,cand,d);
		// dispcand(cand,d);
		// dispsud(sud,d);
		 }
		if(contra(cand,d)==0 || check(sud,d)==1)return;
		else if(ret==1) {ret=0; ret_f=0; eval(1,sud,cand,d,op);}
		break;
}
if(ret==0 && check(sud,d)==0 && contra(cand,d)!=0)
{//cout<<"I'm going deeper \n";
create_copy(cand,sud,d);
h_t(cand,sud,d, op);
}
else if(check(sud,d)==1)return;
}



int main()
{int res;memset(rc,0,sizeof(rc)); memset(cc,0,sizeof(cc)); memset(bc,0,sizeof(bc));
cout<<"================================================================================\n";
cout<<"                       Welcome to the Sudoku Ninja v1.0 \n" ;
cout<<"================================================================================\n";
cout<<"- Designed and Developed by Aseem Dua\n";
cout<<"\n\nPlease enter the name of the input file (along with extension)\n where the sudoku has been stored \n\n";
string ipfle;
ifstream ip;

do{
cin>>ipfle;
ip.open(ipfle.c_str());
if(!ip.is_open())cout<<"\n\nIt seems that the file you have entered has been removed or does not exist.\n Kindly check the location and try again. Rember to add the extension.\n\n";
}while(!ip.is_open());

ofstream op; op.open("sudoku_solution.txt");
int ret_f=0,ret=0;

cout<<"\n\nThe sudoku which you have entered is : - \n\n";
rep(i,0,9){rep(j,0,9){ip>>c; if(c!='.') sud[0][i][j]= c; else sud[0][i][j]='_'; cout<<" "<<sud[0][i][j]<<" ";if((j+1)%3==0)cout<<"|";}
         if((i+1)%3==0)cout<<"\n------------------------------\n";else cout<<"\n";}
cout<<"\n\n Press any key to continue \n\n";



populate(0);
//dispcand(cand,0);

while(1)
{ret=0;
ret_f=0;

rep(i,0,9) {ret_f=elimrow(sud[0][i],i,cand,0); cpy(sud[0][i],i,0); if(ret_f==1) ret=1;}
if(ret==1){/*dispcand(cand,0);*/ fix(sud,cand,0);}

rep(i,0,9) {rep(j,0,9) {col[j]=sud[0][j][i];} {ret_f=elimcol(col,i,cand,0);if(ret_f==1)ret=1;}}
if(ret==1)/*dispcand(cand,0);*/ fix(sud,cand,0);

ret_f= elimbox(cand,sud,0);
if(ret_f==1){ ret=1;/*dispcand(cand,0);*/ fix(sud,cand,0);}

ret_f= freqchk(0,2,cand,0);
if(ret_f==1) {ret=1; /*dispcand(cand,0);*/ fix(sud,cand,0);}

rep(m,0,9)
{ret_f= freqchk(m,1,cand,0);
if(ret_f==1) {ret=1; /*dispcand(cand,0);*/ fix(sud,cand,0);}

ret_f= freqchk(m,0,cand,0);
if(ret_f==1) {ret=1;/*dispcand(cand,0);*/ fix(sud,cand,0);}
}

rep(m,0,9)
{ret_f = chpair(m,0,cand,0);
if(ret_f==1) {ret=1; fix(sud,cand,0);/*dispcand(cand,0);*/}

ret_f = chpair(m,1,cand,0);
if(ret_f==1) {ret=1; fix(sud,cand,0);/*dispcand(cand,0);*/}
}

ret_f = chpair(0,2,cand,0);
if(ret_f==1) {ret=1; fix(sud,cand,0);/*dispcand(cand,0);*/}


if (ret==0)
	break;
}

if(check(sud,0)==0)
{
cout<<"\n\n Nice!!! Your sudoku puzzle is a good one. It may take few more second(s) to get the solution. \n\n";

create_copy(cand,sud,0);
//dispcand(cand, 0);
//dispsud(sud,0);
h_t(cand,sud,0,op);
}

else

{cout<<"\n\n The solution to your sudoku puzzle is :- \n\n";
dispcand(cand,0,op);
++solution_count;
}
cout<<"\n\n The total no. of solutions to your puzzle are:-\t"<<solution_count<<"\n\n";
op<<"\n\n The total no. of solutions to your puzzle are:-\t"<<solution_count<<"\n\n";
cout<<"A solution file (sudoku_solution.txt) has been created for your ready reference\n\n";
cout<<"Thank You for using Sudoku Ninja for your puzzle \n\n";
//cout<<cand<<"\n";
/*rep(d,0,80){
	if(check(sud,d)==1){
cout<<"\n\n After a little thought I feel the solution to your sudoku is :- \n\n";

dispcand(cand,d);
	}
}*/

/*dispcand(cand,0);
dispsud(sud,0);*/
/*res=check(sud,0);
cout<<res<<"\n";*/


return 0;

}
