#cargando archivo y valores qsenecesitan para tratar los datos
A = fopen('train-images','r');   #se abre el archivo

#primeras4  lineasdel archivo
magic_number = fread(A,1,"uint","ieee-be"); #se lee la primera linea que es el numero magico
number_of_images =fread(A,1,"uint","ieee-be");   #numero de imagenes
row =fread(A,1,"uint","ieee-be");      #numero de pixeles de la foto
column =fread(A,1,"uint","ieee-be");

#leyendo 784*10000 pixeles
read =fread(A,"uint8","ieee-be");
fclose(A);

##---------------------------------------------------------
#CARGANDO ARCHIVO CON LOS LABELS PARA CONVERTIRLOS MAS ADELANTE
B = fopen('train-labels','r');
magic_number2 = fread(B,1,"uint","ieee-be");
number_of_images2 =fread(B,1,"uint","ieee-be");
labels = fread(B,"uint8","ieee-be");
fclose(B);

## CREANOD MATRIZ DONDE GUARDAREMOS LOS VALORES DE LOS LABELS
Y = zeros(number_of_images,10);

#factor para matriz aleatoria
epsilon = 1;

#numero de neuronas en la capa oculta
neurons_number = 40;

#organizndo los datos de forma de q queden en una matrix de 784x10000
X = reshape(read,number_of_images,784);

##agregando el termino bias a nuestras caracteristicas
bias_1 = ones(number_of_images,1);
X = [bias_1 , X];

weigth = rand(neurons_number,785)*(2*epsilon) -epsilon;

#creando matrix aleatoria para los pesos intermedios
weigth_2 = rand(10,neurons_number+1)*(2*epsilon) -epsilon;

##----------------------------------------------------------
##FORWARD PROPAGATION
J_theta=[];

for itera = 1:200

  #creando matriz de 20x784 para los pesos con todos sus valores aleatorios enter 1 y -1

  #haciendo las sumatorias (Xi*Wi)
  A = X*weigth';  #producto punto entre las dos matrices dejandolo 1 de 10000x20

  #evaluando todos los valores de la matriz por la funcion H
  t =1./(1+exp(-A));

  #asignamos T a A solo por nomenclatura y ver mejor las operaciones
  A =t;

  #se crea un vector de 1
  matriz_A = ones(number_of_images,1);

  #y se agrega a la matriz para representar el bias term.
  A = [matriz_A,A];


  #calculando los valores de salida de la primera capa con los pesos de la segunda capa  Ai*wi dejando una matriz de 10000 x 10
  A_resultado = weigth_2*A';

  #evaluando los valores de la matriz por la funcion.
  t2 =1./(1+exp(-A_resultado));

  #asignamos el resultado a t2 solo por nomenclatura.
  H = t2';

  ##----------------------------------------------------------
  ## CONVERSION DE LABELS PARA PODERLOS EVALUAR LOS VALORES DE SALIDA PARA CADA FOTO

  for m = 1:number_of_images2
    Y(m,labels(m)+1) =1;
 end


 ##----------------------------------------------------------
 ##BACK PROPAGATION

 #valor seleccionado para los saltos en nuestra funcion
 alpha =0.01;

 ##calculandola derivda evaluando todos los valores de nuestram atriz en lapunion F(x)*(1-F(x))
 H_prima = H.*(1 .- H);
 A_prima = A.*(1 .- A);

 ##para la capa de salida se tiene D3 como el delta de la capa de salida
 D3 = (H - Y).* H_prima;

 #para nuestra capa intermedia D2 como el delta de la capa intermedia
 D2 = (D3*weigth_2).*A_prima;

 #en esta operacion kedan todos los valores con los cuales debemos actualizar nuestros pesos.
 #para la capa intermedia
 Dw2 =  D3'*A;
 #para la capa de entrada
 Dw1 = X'*D2(:,2:neurons_number+1);

 #restamos la matriz de los pesos actuales con el valor de cambio q esta guardado en la matriz y asi obtener los valores deseados de los pesos despues e nuestro entrenamiento
 weigth = weigth - (alpha/number_of_images).*Dw1';

 weigth_2 = weigth_2 - (alpha/number_of_images).*Dw2;

 #la funcion J_theta para representar el error y la funcion de aprnedizaje.
 J_t = (1/number_of_images)*((Y-H).^2);
 #sea agregan los valores calculados a  una matriz para luego graficarlos
 J_theta = [J_theta;sum(J_t)];
 #verificando las iteraciones y el tamanio el vector agregado.
 size(J_theta)
end

#ciclo para graficar todas la fucniones J_theta para cada neurona.
for ite = 1:10
  #para saber en q numero de vnetna 		quiere graficar.
  figure(ite);
  plot(J_theta(:,ite));
end


weigths = fopen('pesos','w');
W1 = fwrite(weigths,weigth,'uint8',"ieee-be");
W2 = fwrite(weigths,weigth_2,'uint8',"ieee-be");
J_theta = fwrite(weigths,J_theta,'uint8',"ieee-be");
fclose(weigths)


#FORWARD PROPAGATION DESPUES DE ENTRENAR
