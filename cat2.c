//cat again, c99 that uses perror()

#include <stdio.h>
#include <stdlib.h>

static int cat(FILE *fpin)
{
  while(!feof(fpin))
  {
    char   buffer[BUFSIZ];
    size_t inbytes = fread(buffer,1,sizeof(buffer),fpin);

    if (ferror(fpin))
      return EXIT_FAILURE;

    do
    {
      size_t outbytes = fwrite(buffer,1,inbytes,stdout);
      if (ferror(stdout))
        return EXIT_FAILURE;
      inbytes -= outbytes;
    } while (inbytes > 0);
  }

  return EXIT_SUCCESS;
}

int main(int argc,char *argv[])
{
  if (argc == 1)
  {
    fprintf(stderr,"usage: %s files...\n",argv[0]);
    return EXIT_FAILURE;
  }

  for (int i = 1 ; i < argc ; i++)
  {
    int   rc1;
    int   rc2;
    FILE *fp = fopen(argv[i],"r");

    if (fp == NULL)
    {
      perror(argv[i]);
      return EXIT_FAILURE;
    }

    if ((rc1 = cat(fp)) != EXIT_SUCCESS)
      perror(argv[i]);

    if ((rc2 = fclose(fp)) != 0)
      perror(argv[i]);

    if ((rc1 != EXIT_SUCCESS) || (rc2 != 0))
      return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
