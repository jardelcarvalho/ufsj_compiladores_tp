int main()
{
  int x = 1, y = 5;
  float a = 2, z = 0;
  int k[10][2]; 
  read z;
  while (y > 1)
  {
      if (y > 2)
         z = z / x;
    x = x * 2;
    y = y -1;
  }
  print(a);
  print(x);
  print(y);
  print(z); 
  print(z >= x || a < 2.5*y);
}
