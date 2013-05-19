#include "cwp.h"

#define LOOKFAC 2   /* Look ahead factor for npfao    */


int main(void) {
  printf("test\n");

  int nt = 100;
  int nfft;     // Number of points in fft trace


  complex *p;
  p = alloc1(nt,sizeof(complex));

  complex *ct;
  ct = alloc1(128,sizeof(complex));

  complex zero;
  zero.r = 0;
  zero.i = 0;

  complex ci;
  ci.r = 0;
  ci.i = 1;



// test sinus
  int i;
  float t=0;
  for (i=0;i<nt;i++) {
    p[i].r = sin(t);
    p[i].i = 0;
    printf("%f %f %fi\n",t,p[i].r,p[i].i);
    t = t+2*M_PI/25.;

  }

  nfft = npfao(nt, LOOKFAC * nt);

  for (i = 0; i<nt; i++) ct[i] = p[i];
  for (i=nt; i<nfft;i++) ct[i] = zero;

  pfacc(1,nfft,ct);
  printf("---------------- %d\n",nfft);

  for (i=0; i<nfft;i++) {
    printf("%f %fi\n",ct[i].r, ct[i].i);
  }

  printf("---------------- %d\n",nfft);


  pfacc(-1,nfft,ct);

  for (i=0; i<nfft;i++) {
    printf("%f %fi\n",ct[i].r, ct[i].i);
  }



  return 0;
}

