package lox;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;

public class Lox {
    static boolean hadError = false;

    public static void main(String[] args) throws IOException {
        if (args.length > 1) {
            System.out.println("Usage: jlox[script]");
            System.exit(64);
        } else if (args.length == 1) {
            runFile(args[0]);
        } else {
            runPrompt();
        }
    }

    private static void runFile(String path) throws IOException {
        byte[] bytes = Files.readAllBytes(Paths.get(path));
        run(new String(bytes, Charset.defaultCharset()));

        if (hadError) System.exit(65);

    }

    private static void runPrompt() throws IOException {
        InputStreamReader input = new InputStreamReader(System.in);
        BufferedReader reader = new BufferedReader(input);

        for(;;) {
            System.out.print("> ");
            String line = reader.readLine();
            if (line == null) break;
            run(line);
            hadError = false;
        }
    }

    private static void run(String source) {
        Scanner scanner = new Scanner(source);
        List<Token> tokens = scanner.scanTokens();

        for (Token token : tokens) {
            System.out.println(token);
        }
    }

    static void error(int line, String message) {
        report(line, "", message);
    }

    private static void report(int line, String where, String message) {
        System.err.println(
                "[line " + line + "] Error" + where + ": " + message
        );
        hadError = true;
    }

    abstract static class Expr {
      interface Visitor<R> {
        R visitBinaryExpr(Binary expr);
        R visitGroupingExpr(Grouping expr);
        R visitLiteralExpr(Literal expr);
        R visitUnaryExpr(Unary expr);
      }
      static class Binary extends Expr {
        Binary(Expr left, Token operator, Expr right) {
          this.left = left;
          this.operator = operator;
          this.right = right;
        }

        @Override
        <R> R accept(Visitor<R> visitor) {
          return visitor.visitBinaryExpr(this);
        }

        final Expr left;
        final Token operator;
        final Expr right;
      }
      static class Grouping extends Expr {
        Grouping(Expr expression) {
          this.expression = expression;
        }

        @Override
        <R> R accept(Visitor<R> visitor) {
          return visitor.visitGroupingExpr(this);
        }

        final Expr expression;
      }
      static class Literal extends Expr {
        Literal(Object value) {
          this.value = value;
        }

        @Override
        <R> R accept(Visitor<R> visitor) {
          return visitor.visitLiteralExpr(this);
        }

        final Object value;
      }
      static class Unary extends Expr {
        Unary(Token operator, Expr right) {
          this.operator = operator;
          this.right = right;
        }

        @Override
        <R> R accept(Visitor<R> visitor) {
          return visitor.visitUnaryExpr(this);
        }

        final Token operator;
        final Expr right;
      }

      abstract <R> R accept(Visitor<R> visitor);
    }
}












