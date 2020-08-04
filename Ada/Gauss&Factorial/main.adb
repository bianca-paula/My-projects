-- Write a program that asks the user
-- for a number n and gives them the
-- possibility to choose between
-- computing the sum, computing the product or
-- number of permutations of 1,..,n

with Gnat.IO; use Gnat.IO;
with Text_IO;

procedure Main is
   number, ok: Integer;
   sum : Integer := 0;
   product : Integer := 1;
   index : Integer := 1;

begin
   Put ("Please enter a number: ");
   New_Line;
   Get (number);
   New_Line;
   Put ("Your number is: ");
   Put (number);
   New_Line;
   Put("Choose :");
   New_Line (2);
   Put("1) Compute the sum of first n natural numbers;");
   New_Line (2);
   Put("2) Compute the product of first n natural numbers;");
   New_Line (2);
   Get (ok);

   case ok is
      when 1 =>
         Put ("The sum of first ");
         Put (number);
         Put (" numbers is: ");
         sum := (number*number+number)/2;
         Put (sum);
         New_Line;
      when 2 =>
         Put ("The product of first ");
         Put (number);
         Put (" numbers is: ");
         for index in 1 .. number loop
            product := product*index;
         end loop;
         Put (product);
         New_Line;
      when others =>
         Put ("Invalid choice!");
         New_Line;
         --end if;
   end case;
   Put ("End of the program!");
   New_Line;

   null;
end Main;
