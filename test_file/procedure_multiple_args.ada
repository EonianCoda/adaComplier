{ This test program computes the Nth Fibonacci number
    using recursion and iteration. }

program computeFib

-- global variables
declare
  n: constant := 8;

-- iterative function
procedure itFibonacci (n: integer; s:float; j:string) return integer
declare
  Fn: integer;
  FNminus1: integer;
  temp: integer;

begin
  Fn := 1;
  FNminus1 := 1;
  while (n > 2) loop
    begin
      temp := Fn;
      Fn := Fn + FNminus1;
      FNminus1 := temp;
      n := n - 1;
    end;
  end loop;
  return Fn;
end;
end itFibonacci;
procedure apple (p,h :float) return float
begin
  read p;
  read Fn;
end;
end apple;
-- main program 
begin
  print "N: ";
  println n;
  print "Result of iterative computation:";
  print apple(1.0+9.0,2.0);
end
end computeFib
