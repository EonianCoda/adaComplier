class example
{
	/* 2: program example */
	/* 3:     declare */
	field static int a
	/* 4:         a; */
	field static int b = 1
	/* 5:         b : integer := 1; */
	/* 6:         c : constant := 1 + 1 * 5 _ 5 + 1; */
	/* 7:         d : constant : integer := -c; */
	/* 8:         e : constant : string := "Var e"; */
	/* 9:         f : constant := "constant"; */
	/* 10:     procedure voidFun () */
	method public static void voidFun()
	max_stack 15
	max_locals 15
	{
		/* 11:         begin */
		getstatic java.io.PrintStream java.lang.System.out
		ldc "hello"
		invokevirtual void java.io.PrintStream.print(java.lang.String)
		/* 12:             print "hello"; */
		/* 13:         end; */
		return
	}
	/* 14:     end voidFun; */
	/* 15:  */
	/* 16:     procedure integerFun (a : integer; b : integer) return integer */
	method public static int integerFun(int, int)
	max_stack 15
	max_locals 15
	{
		/* 17:         begin */
		iload 0
		iload 1
		iadd
		ireturn
		/* 18:             return a + b; */
		/* 19:         end; */
	}
	/* 20:     end integerFun; */
	/* 21:  */
	method public static void main(java.lang.String[])
	max_stack 15
	max_locals 15
	{
		/* 22:     begin */
	Label2:
		getstatic int example.b
		sipush 10
		if_icmple Label6
		goto Label11
	Label6:
		/* 23:         while (b <= 10) loop */
		/* 24:         begin */
		getstatic java.io.PrintStream java.lang.System.out
		getstatic int example.b
		invokevirtual void java.io.PrintStream.println(int)
		/* 25:             println b; */
		getstatic int example.b
		sipush 1
		iadd
		putstatic int example.b
		/* 26:             b := b + 1; */
		/* 27:         end; */
		goto Label2
		/* 28:         end loop; */
		/* 29:  */
		/* 30:  */
	Label11:
		sipush 1
		putstatic int example.a
	Label12:
		getstatic int example.a
		sipush 10
		if_icmple Label15
		goto Label45
	Label15:
		/* 31:         for (a in 1 .. 10) loop */
		/* 32:         begin */
		getstatic int example.a
		sipush 7
		if_icmpgt Label25
		goto Label21
	Label21:
		getstatic int example.a
		sipush 2
		if_icmple Label25
		goto Label35
	Label25:
		/* 33:             if(a > 7 or a <= 2) then */
		/* 34:                 begin */
		getstatic int example.a
		sipush 1
		if_icmpeq Label31
		goto Label33
	Label31:
		/* 35:                     if(a = 1) then */
		getstatic java.io.PrintStream java.lang.System.out
		ldc "a=1"
		invokevirtual void java.io.PrintStream.println(java.lang.String)
		/* 36:                         println "a=1"; */
		goto Label43
	Label33:
		/* 37:                     else */
		invokestatic void example.voidFun()
		/* 38:                         voidFun(); */
		/* 39:                     end if; */
		/* 40:                 end; */
		goto Label43
	Label35:
		/* 41:             else */
		/* 42:                 begin */
		getstatic int example.a
		sipush 5
		if_icmpeq Label41
		goto Label42
	Label41:
		/* 43:                     if(a = 5) then */
		invokestatic void example.voidFun()
		/* 44:                         voidFun(); */
		/* 45:                     end if; */
	Label42:
		getstatic java.io.PrintStream java.lang.System.out
		getstatic int example.a
		sipush 2
		getstatic int example.a
		imul
		invokestatic int example.integerFun(int, int)
		invokevirtual void java.io.PrintStream.println(int)
		/* 46:                     println integerFun(a, 2 * a); */
		/* 47:                 end; */
		/* 48:             end if; */
		/* 49:         end; */
	Label43:
		getstatic int example.a
		sipush 1
		iadd
		putstatic int example.a
		goto Label12
		/* 50:         end loop; */
		/* 51:  */
		/* 52:          */
	Label45:
		getstatic java.io.PrintStream java.lang.System.out
		ldc "final loop"
		invokevirtual void java.io.PrintStream.println(java.lang.String)
		/* 53:         println "final loop"; */
		/* 54:     end; */
		return
	}
}