#include "minet.h"
SEXP buildMIMgaussian(SEXP Rdata, SEXP Rnrows, SEXP Rncols)
{
      const double *data;
      const int *nrows,*ncols;
      double *res, mi;
      SEXP Rres;
      PROTECT(Rdata = AS_NUMERIC(Rdata));
      PROTECT(Rnrows= AS_INTEGER(Rnrows));
      PROTECT(Rncols= AS_INTEGER(Rncols));
      data = NUMERIC_POINTER(Rdata);
      nrows= INTEGER_POINTER(Rnrows);
      ncols= INTEGER_POINTER(Rncols);      
      PROTECT(Rres = NEW_NUMERIC((*ncols)*(*ncols)));
      res = NUMERIC_POINTER(Rres);
      for( int i=1; i<*ncols; ++i )
            for( int j=0; j<i; ++j ) {
                  mi = squarecorrelation(data,*nrows,*ncols,i,j);
                  res[j*(*ncols)+i] = res[i*(*ncols)+j] = mi;
            }
      for( int i=0; i<*ncols; ++i ) res[i*(*ncols)+i]=0;
      UNPROTECT(4);
      return Rres;
}
SEXP buildMIMshrink(SEXP Rdata, SEXP Rnrows, SEXP Rncols)
{
      const double *data;
      const int *nrows,*ncols;
      double *res, mi;
      SEXP Rres;
      PROTECT(Rdata = AS_NUMERIC(Rdata));
      PROTECT(Rnrows= AS_INTEGER(Rnrows));
      PROTECT(Rncols= AS_INTEGER(Rncols));
      data = NUMERIC_POINTER(Rdata);
      nrows= INTEGER_POINTER(Rnrows);
      ncols= INTEGER_POINTER(Rncols);      
      PROTECT(Rres = NEW_NUMERIC((*ncols)*(*ncols)));
      res = NUMERIC_POINTER(Rres);
      for( int i=1; i<*ncols; ++i )
            for( int j=0; j<i; ++j ) {
                  mi = minformation( data, *nrows, *ncols, i, j, 's' );
                  res[j*(*ncols)+i] = res[i*(*ncols)+j] = mi;
            }
      for( int i=0; i<*ncols; ++i ) res[i*(*ncols)+i]=0;
      UNPROTECT(4);
      return Rres;
}
SEXP buildMIMempirical(SEXP Rdata, SEXP Rnrows, SEXP Rncols)
{
      const double *data;
      const int *nrows,*ncols;
      double *res, mi;
      SEXP Rres;
      PROTECT(Rdata = AS_NUMERIC(Rdata));
      PROTECT(Rnrows= AS_INTEGER(Rnrows));
      PROTECT(Rncols= AS_INTEGER(Rncols));
      data = NUMERIC_POINTER(Rdata);
      nrows= INTEGER_POINTER(Rnrows);
      ncols= INTEGER_POINTER(Rncols);      
      PROTECT(Rres = NEW_NUMERIC((*ncols)*(*ncols)));
      res = NUMERIC_POINTER(Rres);
      for( int i=1; i<*ncols; ++i )
            for( int j=0; j<i; ++j ) {
                  mi = minformation( data, *nrows, *ncols, i, j, 'e' );
                  res[j*(*ncols)+i] = res[i*(*ncols)+j] = mi;
            }
      for( int i=0; i<*ncols; ++i ) res[i*(*ncols)+i]=0;
      UNPROTECT(4);
      return Rres;
}
SEXP buildMIMmillermadow( SEXP Rdata, SEXP Rnrows, SEXP Rncols )
{
      const double *data;
      const int *nrows,*ncols;
      double *res, mi;
      SEXP Rres;
      PROTECT(Rdata = AS_NUMERIC(Rdata));
      PROTECT(Rnrows= AS_INTEGER(Rnrows));
      PROTECT(Rncols= AS_INTEGER(Rncols));
      data = NUMERIC_POINTER(Rdata);
      nrows= INTEGER_POINTER(Rnrows);
      ncols= INTEGER_POINTER(Rncols);      
      PROTECT(Rres = NEW_NUMERIC((*ncols)*(*ncols)));
      res = NUMERIC_POINTER(Rres);
      for( int i=1; i<*ncols; ++i )
            for( int j=0; j<i; ++j ) {
                  mi = minformation( data, *nrows, *ncols, i, j, 'm' );
                  res[j*(*ncols)+i] = res[i*(*ncols)+j] = mi;
            }
      for( int i=0; i<*ncols; ++i ) res[i*(*ncols)+i]=0;
      UNPROTECT(4);
      return Rres;
}
SEXP buildMIMdirichlet(SEXP Rdata, SEXP Rnrows, SEXP Rncols)
{
      const double *data;
      const int *nrows,*ncols;
      double *res, mi;
      SEXP Rres;
      PROTECT(Rdata = AS_NUMERIC(Rdata));
      PROTECT(Rnrows= AS_INTEGER(Rnrows));
      PROTECT(Rncols= AS_INTEGER(Rncols));
      data = NUMERIC_POINTER(Rdata);
      nrows= INTEGER_POINTER(Rnrows);
      ncols= INTEGER_POINTER(Rncols);      
      PROTECT(Rres = NEW_NUMERIC((*ncols)*(*ncols)));
      res = NUMERIC_POINTER(Rres);
      for( int i=1; i<*ncols; ++i )
            for( int j=0; j<i; ++j ) {
                  mi = minformation( data, *nrows, *ncols, i, j, 'c' );
                  res[j*(*ncols)+i] = res[i*(*ncols)+j] = mi;
            }
      for( int i=0; i<*ncols; ++i ) res[i*(*ncols)+i]=0;
      UNPROTECT(4);
      return Rres;
}
double squarecorrelation(const double *d, int N, int n, int i, int j) 
{
      double xsum=0, ysum=0, xsquare=0, ysquare=0, samples=0, xy=0, x, y;
      for(int s=0; s<N; s++) 
            if( d[s+i*N]!=NA && d[s+j*N]!=NA )
            {
                x = d[s+i*N];
                y = d[s+j*N];
                xsum += x;
                xsquare += x*x;
                ysum += y;
                ysquare += y*y;
                xy += x*y;
                ++samples;
            }
      double num = xy - (xsum*ysum)/samples;
      double den1 = xsquare - (xsum*xsum)/samples;
      double den2 = ysquare - (ysum*ysum)/samples;
      if(den1 == 0 || den2 == 0 || num == 0) return 0;
      else return (num*num)/(den1*den2);
}
double minformation(const double *d, int N, int n, int i, int j, char c) {
      map< vector<double> ,int > freqi;
      map< vector<double> ,int > freqj;
      map< vector<double> ,int > freqij;
      vector<double> sel;
      double Hi, Hj, Hij;
      int    ni=0, nj=0, nij=0;
      for(int s = 0; s < N; s++) 
          if(d[s+i*N]!=NA && d[s+j*N]!=NA ){
            sel.clear();
            sel.push_back(d[s+i*N]);  freqi[sel]++; ni++;
            sel.push_back(d[s+j*N]);  freqij[sel]++; nij++;
            sel.clear();
            sel.push_back(d[s+j*N]);  freqj[sel]++; nj++;
            }            
            else if( d[s+i*N]!=NA ) { sel.push_back(d[s+i*N]);  freqi[sel]++; ni++; }
            else if( d[s+j*N!=NA] ) { sel.push_back(d[s+j*N]);  freqj[sel]++; nj++; }                  
      if( c=='s' ) { // shrink
            Hi = entropy_shrink(freqi,ni);
            Hj = entropy_shrink(freqj,nj);
            Hij = entropy_shrink(freqij,nij);
      }
      else if( c=='b' ) { //shrink2
            Hi = entropy_shrink2(freqi,ni);
            Hj = entropy_shrink2(freqj,nj);
            Hij = entropy_shrink2(freqij,nij);
      }
	else if( c=='c' ) { //dirichlet Schurmann-Grassberger
            Hi = entropy_dirichlet(freqi,ni, 1/freqi.size());
            Hj = entropy_dirichlet(freqj,nj, 1/freqj.size());
            Hij = entropy_dirichlet(freqij,nij, 1/freqij.size());
      }
      else if( c=='e' ) { //empirical
            Hi = entropy_empirical(freqi,ni);
            Hj = entropy_empirical(freqj,nj);
            Hij = entropy_empirical(freqij,nij);
      }
      else if( c=='m' ) { //miller-madow
            Hi = entropy_empirical(freqi,ni) + double(freqi.size()-1)/(2*double(ni));
            Hj = entropy_empirical(freqj,nj) + double(freqj.size()-1)/(2*double(nj));;
            Hij = entropy_empirical(freqij,nij) + double(freqij.size()-1)/(2*double(nij));
      }
      double mi = (Hi+Hj-Hij);
      if(mi<0) return 0;
      return mi;      
}
double digamma(double z) {
      if(z<=0) return 0;
      double zp, zpr, zprs, digam = 0;
      zp = z;
      while(zp < 30) {
            zpr = 1/zp;
            digam -= zpr;
            zp++;
      }
      zpr = 1/zp;
      zprs = zpr * zpr;
      digam += log(zp)+zpr*(-0.5+zpr*(-1.0/12.0+zprs*(1.0/120.0-zprs/252.0)));
      return digam;
}
double entropy_empirical(map< vector<double> ,int > frequencies, int nb_samples) {
      double e = 0;
      for (map< vector<double> ,int>::const_iterator iter = frequencies.begin(); iter != frequencies.end(); ++iter)
            e -= iter->second * log(iter->second);
      return log(nb_samples) + e/nb_samples;
}
double entropy_dirichlet(map< vector<double> ,int > frequencies, int nb_samples, double beta) {
      double e = 0;
      for (map< vector<double> ,int>::const_iterator iter = frequencies.begin(); iter != frequencies.end(); ++iter)
            e+=(iter->second+beta)*(digamma(nb_samples+(frequencies.size()*beta)+1)-digamma(iter->second+beta+1));
      return e/(nb_samples+(frequencies.size()*beta));
}
double entropy_shrink2(map< vector<double> ,int > frequencies, int nb_samples) 
{
      double w = 0;
      int p = frequencies.size(), n2 = nb_samples*nb_samples; 
      double lambda, beta;
      for (map< vector<double> ,int>::const_iterator iter = frequencies.begin(); iter != frequencies.end(); ++iter) 
            w += iter->second*iter->second;
      lambda = p*(n2 - w)/((nb_samples-1)*(w*p - n2));
      if(lambda >= 1)
            return -log(1.0/p);
      else {
            beta = (lambda/(1-lambda))*nb_samples/frequencies.size();
            return entropy_dirichlet(frequencies, nb_samples, beta);
      }
}
double entropy_shrink(map< vector<double> ,int > frequencies, int nb_samples) 
{
      double lambda, w=0, e=0;
      int p = frequencies.size(), n2 = nb_samples*nb_samples; 
      for (map< vector<double> ,int>::const_iterator iter = frequencies.begin(); iter != frequencies.end(); ++iter) 
            w += iter->second*iter->second;
      lambda = p*(n2 - w)/((nb_samples-1)*(w*p - n2));
	  if (lambda>1)
		lambda = 1; 
	  for (map< vector<double> ,int>::const_iterator iter = frequencies.begin(); iter != frequencies.end(); ++iter) {
			 double pxi = lambda*1/frequencies.size()+(1-lambda)*iter->second/nb_samples;
			 e -= pxi * log(pxi);
	  }
      return e;
}
