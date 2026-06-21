#include <iostream>
using namespace std;
int gcd(int a,int b){
    while(b){int t=b;
        b=a%b;
        a=t;}
    return a;}
long long mod_pow(long long b,long long e,long long m){
    long long r=1;
    b%=m;
    while(e){
        if(e&1) r=(r*b)%m;
        b=(b*b)%m;
        e/=2;}
    return r;}
bool is_prime(long long n){
    if(n==2) return true;
    if(n<2 || n%2==0) return false;
    for(long long i=3;i*i<=n;i+=2)
        if(n%i==0) return false;
    return true;}
bool primitive_root(long long a,long long p){
    if(!is_prime(p) || gcd(a,p)!=1)	return false;
    for(long long i=1;i<p-1;i++)
        if(mod_pow(a,i,p)==1)		return false;
    return mod_pow(a,p-1,p)==1; }
long long discrete_log(long long a,long long b,long long p){
    if(!is_prime(p) || a<=0 || b<=0)	return -1;
    if(!primitive_root(a,p))		return -2;
    for(long long i=0;i<p;i++)
        if(mod_pow(a,i,p)==b%p)	return i;
    return -1;}
int main(){
    long long a,b,p;
    cout<<"Enter a: ";	cin>>a;
    cout<<"Enter b: ";	cin>>b;
    cout<<"Enter p: ";	cin>>p;
    long long ans=discrete_log(a,b,p);
    if(ans==-1)	cout<<"Invalid input\n";
    else if(ans==-2)	cout<<"a is not primitive root\n";
    else		cout<<"Discrete Log = "<<ans<<endl;
    return 0;
}

