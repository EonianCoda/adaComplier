class example
{
	/* 2: program example */
	/* 3:     declare */
	field static int a = 5
	/* 4:         a : integer := 5; */
	field static int b = 1
	/* 5:         b : boolean := 5 > 3; */
	method public static void main(java.lang.String[])
	max_stack 15
	max_locals 15
	{
		/* 6:     begin */
		getstatic int example.a
		sipush 5
		if_icmpgt Label5
		goto Label9
	Label5:
		getstatic int example.a
		sipush 10
		if_icmplt Label17
		goto Label9
	Label9:
		getstatic int example.a
		sipush 1
		if_icmpeq Label17
		goto Label13
	Label13:
		getstatic int example.a
		sipush 2
		if_icmpeq Label17
		goto Label19
	Label17:
		/* 7:         if((a > 5 and a < 10) or (a = 1 or a = 2)) then */
		getstatic java.io.PrintStream java.lang.System.out
		iconst_1
		iconst_1
		if_icmpeq BoolTrue0
		ldc "false"
		goto BoolPrint0
		BoolTrue0:
		ldc "true"
		BoolPrint0:
		invokevirtual void java.io.PrintStream.println(java.lang.String)
		/* 8:             println true; */
		goto Label20
	Label19:
		/* 9:         else */
		getstatic java.io.PrintStream java.lang.System.out
		iconst_0
		iconst_1
		if_icmpeq BoolTrue1
		ldc "false"
		goto BoolPrint1
		BoolTrue1:
		ldc "true"
		BoolPrint1:
		invokevirtual void java.io.PrintStream.println(java.lang.String)
		/* 10:             println false; */
		/* 11:         end if; */
		/* 12:  */
	Label20:
		getstatic java.io.PrintStream java.lang.System.out
		getstatic int example.b
		getstatic int example.a
		sipush 6
		if_icmpeq 		BoolTrue2
		iconst_0
		goto BoolOpEnd2
		BoolTrue2:
		iconst_1
		BoolOpEnd2:
		iand
		iconst_1
		if_icmpeq BoolTrue3
		ldc "false"
		goto BoolPrint3
		BoolTrue3:
		ldc "true"
		BoolPrint3:
		invokevirtual void java.io.PrintStream.println(java.lang.String)
		/* 13:         println b and (a = 6); */
		/* 14:     end; */
		return
	}
}