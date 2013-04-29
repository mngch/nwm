#include <math.h>
#include <stdio.h>
#include <stdlib.h>




int init_gauss(int nx, float *p, float *pp);
int init_velocity(int nx, float *c2);
int diff(float *p, float *diffarray, float dx, int nx);
int check_stability(float dx, float vmax, float dt);

int main(void) {
  int nx = 100;   // number of gridpoints
  float tmax = 0.05;// time to run
  float dt = 0.003;//
  float dx=10;

  int nt = tmax/dt;

  int ix;
  int it;

  float pmax;




  // pressure arrays
  float *par;
  float *ppar;
  float *tmpar;
  par = (float *) malloc(nx*sizeof(float));
  ppar = (float *) malloc(nx*sizeof(float)); // pressure previous timestep;
  tmpar = (float *) malloc(nx*sizeof(float));

  // pointers to arrays for easy swapping
  float *p = par;
  float *pp = ppar;
  float *tmp = tmpar;

  // differential array
  float *diffarray;
  diffarray = (float *) malloc(nx*sizeof(float));



  // velocity squared array
  float *c2;
  c2 = (float *) malloc(nx*sizeof(float));

  // outputfile
  char filename[20]="test";
  FILE * pFile;
  pFile = fopen (filename,"wb");

  // START /////////////////////////////////////////////
  init_gauss(nx,p,pp);
  init_velocity(nx,c2);



  // TIMESTEPS
  for (it=0;it<nt;it++) {

    // calculate diff
    diff(p,diffarray,dx,nx);
    // SPACE
    for (ix=0;ix<nx;ix++) {
      tmp[ix] = -pp[ix] + 2*p[ix] + c2[ix]*c2[ix]*dt*dt*diffarray[ix];
      pmax = (tmp[ix] > pmax ? tmp[ix] : pmax);
    }
    printf("timestep %d\tat t=%f\tpmax=%f\n",it,it*dt,pmax);

    fwrite(p,sizeof(p),nx,pFile);
    // swap arrays
    //pp= par;
    //p = tmpar;
    int i;
    for (i=0;i<nx;i++) {
      pp[i] = p[i];
      p[i] = tmp[i];

    }
  }

  check_stability(dx, 3000, dt);


  // END
  fclose(pFile);
  return 0;
}


int init_gauss(int nx, float *p, float *pp) {
  // initialize pressure fields

  int i;
  for (i=0;i<=nx;i++) {
    pp[i] = exp(-pow(((nx/2-i)*0.4),2));
    p[i] = exp(-pow(((nx/2-i)*0.4),2));
  }

  return 0;
}

int diff(float *p, float *diffarray, float dx, int nx) {
  // calculate differential
  
  float dx2 = dx*dx;
  int i, il, ir;      // actual point, point left, point right

  for (i=0; i<nx; i++) {
    il = (i+nx-1) % nx;   // cyclic borders
    ir = (i+1) % nx;
    diffarray[i] = (p[ir]-2*p[i]+p[il])/dx2;
  }
    return 0;
}

int init_velocity(int nx, float *c2) {
  int i;
  for (i=0;i<nx;i++) {
    if (i<75) {
      c2[i] = 3000;
    } else {
      c2[i] = 2000;
    }
  }
  return 0;
}

int check_stability(float dx, float vmax, float dt) {
  float alpha;
  float maxt;
  

  alpha = vmax*dt/dx;
  maxt = dx/vmax;

  printf("dt =\t \t %f \t (should be lesser than %f)\n",dt,maxt);
  printf("alpha = \t %f \t (should be below 1)\n",alpha);
  return 0;
}
