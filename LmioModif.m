function L = LmioModif(x, r)

%Este código es para no tener que armar el RP y después calcularle L.
%Directamente calcula L a partir del vector de datos.

% Sirve sólo para matriz antisimétrica y Lmin = 2
% No usa lo de normalizar delta con la desviación estándar, sinó que normaliza el vector de entrada

%%

N = length(x);
%Delta = r*std(x);

maxX = max(x);
minX = min(x);
ampX = 1/(maxX - minX);
x = ampX*(x - minX);

Ltotal = 0; %El largo de la diagonal total que se va incrementando
diagonales = 0; %La cantidad de cortes que aparecen
for retardo = 1:N - 2 %Va barriendo distancias temporales (posiciones de la RP en forma diagonal). Es N - 2 por que Lmin = 2.
    diagonal = 0; %El largo de la diagonal cortita actual
    for i = 1:N - retardo %Va barriendo las posiciones del vector
        distancia = abs(x(i) - x(i + retardo));
        if distancia < r %Hay diagonal!
            diagonal = diagonal + 1; %Este valor siempre está atrazado por uno
        else
            if  diagonal >= 2 %Si la diagonal actual es mayor que 2
                Ltotal = Ltotal + diagonal; %Incrementa la diagonal total
                diagonales = diagonales + 1; %Cuenta que hubo una diagonal
            end
            diagonal = 0;
        end
    end
end

L = Ltotal/diagonales; %Si no aparece ninguna diagonal más larga que 2 L = NaN. Si aparecen solo de largo 1 L = 1.