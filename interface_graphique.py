from tkinter import *
import sys

fenetre = Tk()

#GESTION DU FICHIER
taille=0
liste =[]
f=open("fichier.txt","r")
f1=f.read()
if f1[0]=='I' :
        canvas = Canvas (fenetre,width=200,height=200, background = 'white')
        canvas.create_text(100,100, text="INSATISFAISABLE", font="Arial 10 italic", fill='red')
        canvas.pack()
        fenetre.mainloop()
        sys.exit ()
for x in f1:
    taille=taille+1
    liste.append(x)
    if x=='\n' :
        liste.pop()
n=(taille/2)**0.5

m=n
n=n*100
canvas = Canvas (fenetre,width=n,height=n, background = 'white')
j=0

#CREATION DE L'IMAGE
while j<n :
    j=j+100
    canvas.create_line(0,j,n,j)
    canvas.create_line(j,0,j,n)

i=0
x=n/(m*2)
y=x
k=0
while k<n :
    j=0
    x=n/(m*2)
    while j<m :
        canvas.create_text(x,y, text=liste[i], font="Arial 16 italic", fill="blue")
        i=i+1
        j=j+1
        x=x+100
    y=y+100
    k=k+100

canvas.pack()
fenetre.mainloop()
