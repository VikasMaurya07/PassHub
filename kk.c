#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_WEBSITE_LENGTH 50
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define FILENAME "passwords.txt"
#define X 11
#define Y 7

int n, t, i;
long int e, d, temp[50], j, en[50];
char website[MAX_WEBSITE_LENGTH], username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];

int prime(long int);
void encrypt();
void decrypt();

int main()
{
  FILE *fp;

  // Get input from user
  printf("Enter website: ");
  fgets(website, MAX_WEBSITE_LENGTH, stdin);
  printf("Enter username: ");
  fgets(username, MAX_USERNAME_LENGTH, stdin);
  printf("Enter password: ");
  fgets(password, MAX_PASSWORD_LENGTH, stdin);

  // Remove newline characters from input
  website[strcspn(website, "\n")] = 0;
  username[strcspn(username, "\n")] = 0;
  password[strcspn(password, "\n")] = 0;

  // Open file for writing in binary mode
  fp = fopen(FILENAME, "wb");
  if (fp == NULL) {
    printf("Error opening file\n");
    exit(1);
  }

  // Encrypt the password
  for (i = 0; password[i] != NULL; i++)
    temp[i] = password[i];
  n = X * Y;
  t = (X - 1) * (Y - 1);
  e = 7; // Hardcoded encryption key
  encrypt();

  // Write encrypted data to file
  fwrite(website, sizeof(char), strlen(website), fp);
  fwrite(username, sizeof(char), strlen(username), fp);
  fwrite(en, sizeof(long int), i, fp);

  // Close file
  fclose(fp);

  printf("Password saved successfully!\n");

  return 0;
}

int prime(long int pr)
{
  int i;
  j = sqrt(pr);
  for (i = 2; i <= j; i++)
  {
    if (pr % i == 0)
      return 0;
  }
  return 1;
}

//function to encrypt the message
void encrypt()
{
  long int pt, ct, key = e, k, len;
  i = 0;
  len = strlen(password);
  while (i != len)
  {
    pt = temp[i];
    pt = pt - 96;
    k = 1;
    for (j = 0; j < key; j++)
    {
      k = k * pt;
      k = k % n;
    }
    en[i] = k + 96;
    i++;
  }
  en[i] = -1;
}

void decrypt()
{
  long int pt, ct, key = d, k;
  i = 0;
  while (en[i] != -1)
  {
    ct = temp[i];
    k = 1;
    for (j = 0; j < key; j++)
    {
      k = k * ct;
      k = k % n;
    }
    pt = k + 96;
    password[i] = pt;
    i++;
  }
  password[i] = -1;
}