/*
Adott dátumhoz hozzáadott munkanapok utáni dátum kiszámítása.
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <date.h>

#define MAXUNN 8
static int unho[MAXUNN] = {1,  3, 5,  8, 10, 11, 12, 12};
static int unap[MAXUNN] = {1, 15, 1, 20, 23,  1, 25, 26};

static int hetvege;
static char s1[20];

int dt_eq(DT_DATE *d1, DT_DATE *d2)
{
  if ((DT_year(d1) == DT_year(d2))
    &&(DT_month(d1) == DT_month(d2))
    &&(DT_day(d1) == DT_day(d2)))
  {
    return 0;
  }
  return -1;
}

int is_unnep(int h, int n)
{
  int i;

  for (i=0; i<MAXUNN; i++)
  {
    if ((h == unho[i]) && (n == unap[i]))
      return 0;
  }
  return -1;
}

int proc(int y, int m, int d, int x, char *s)
{
  DT_DATE *dat, *husv, *punk;
  int i, j, k;

  dat = DT_mkdate(y,m,d);

  hetvege = 0;
  j = DT_dow(dat);
  if ((j==0) || (j==6))
    hetvege = 1;

  husv = DT_copy_date(dat);
  (void)DT_easter(husv);
  DT_add_days(husv, 1);

  if (dt_eq(dat, husv) == 0)
    hetvege = 1; //valójában húsvét!
       
  punk = DT_copy_date(husv);
  DT_add_days(punk, 49);

  if (dt_eq(dat, punk) == 0)
    hetvege = 1; //valójában pünkösd!
       
  if (dat == NULL)
  {
    fprintf(stderr, "*** DT_mkdate_die(): said \"%s\"\n",
     strerror(errno));                                         
    return -1;
  }
  
  if (m==2 && d==29)
    if (!DT_is_leap_year(dat))
    {
      fprintf(stderr, "%d nem szökőév!\n", y);
      return -1;
    }

  k = x;
  for (i=0; i<k; i++)
  {
    DT_add_days(dat, 1);
    j = DT_dow(dat);
    if ((j==0) || (j==6))
    {
      k++;
    }
    else
    {
      if (is_unnep(DT_month(dat), DT_day(dat)) == 0)
        k++;
    }
    if (dt_eq(dat, husv) == 0)
      k++;
    if (dt_eq(dat, punk) == 0)
      k++;
  }
  
  strcpy(s, DT_ascii(dat, DT_UNIVERSAL_FORMAT));

  DT_rmdate(dat);

  return 0;
}

int main(int ac, char **av)
{
  int e,h,n,x;

  if (ac == 5)
  {
    e = atoi(av[1]);
    h = atoi(av[2]);
    n = atoi(av[3]);
    if (n > DT_days_this_month_q(e, h))
    {
      fprintf(stderr, "Hibás dátum!\n");
      return -1;
    }
    x = atoi(av[4]);

    if (is_unnep(h, n) != 0)
    {
      proc(e,h,n,x,s1);
      if (hetvege == 0)
      {
        printf("%d.%d.%d. +%d", e,h,n,x);
        printf(" = %s\n", s1);
      }
    }
  }
  else
  {
    printf("%s: <év hó nap +nap>\n", av[0]);
    return -1;
  }
  return 0;
}

