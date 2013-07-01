;*************************************************
;* Compo pour la demo party CRAU04               *
;* --------------------------------------------- *
;* Auteur      : Ecureuil                        *
;* Date        : 2004 / 12 / 11                  *
;* Compilateur : DEVPAC 3.1 sous Steem debug 3.1 *
;* --------------------------------------------- *
;* Commentaires :                                *
;* ------------                                  *
;*                                               *
;*************************************************

	include constant.i		; on inclus les constantes

	; On passe en mode superviseur
	clr.l	-(a7)
	move.w	#SUPERVISEUR,-(a7)	; 20h = Superviseur
	trap	#BIOS			; du bios
	addq.l	#6,a7	

	; on sauve l'ancienne valeur pour revenir en mode utilisateur proprement

	move.l d0,sauve_s

	; on sauve la palette de couleur
	
	movem.l $FFFF8240,d0-d7
	movem.l d0-d7,sauve_palette

	; on met la premiere couleur de la palette a 0 cad noir. les bordures de
	; l'ecran seront donc noire
	
	move.w #0,$FFFF8240.w
	move.w #$700,$FFFF8242.w
	move.w #$700,$FFFF8244.w
	move.w #$070,$FFFF8246.w
	move.w #$007,$FFFF8248.w
	move.w #$500,$FFFF824a.w
	move.w #$050,$FFFF824c.w
	move.w #$005,$FFFF824e.w
	move.w #$400,$FFFF8250.w
	move.w #$040,$FFFF8252.w
	move.w #$004,$FFFF8254.w
	move.w #$340,$FFFF8256.w
	move.w #$043,$FFFF8258.w
	move.w #$343,$FFFF825a.w


	; on utilise la ligne A pour cacher le pointeur de la souris afin de
	; ne pas avoir la disgracieuse guepe ;op
	; fonction line A no 10. Le mode line a est invoque via l'octet de poid
	; fort du WORD $A0 et l'octet de poid faible indique la fonction a savoir
	; $0A soit 10 en decimal.
	
	dc.w $a00a

	; On choppe l'adresse de l'ecran a la maniere crade et on la met en a0
	; puis on boucle 7999 fois soit 32000/4 = 8000 et 8000-1 car le 0 est
	; compris ds la boucle :p
	move.l $44e.w,a0
	move.l #7999,d0
	
affiche_ecran1:	
	
	; On vide les bits se trouvant a l'adresse a0 et on incremente son pointeur de 4
	; octets .l = longword = DWORD.
	clr.l (a0)+

	;on effectue la boucle tant que d0 n'est pas inferieur a 0
	dbra d0,affiche_ecran1

	move.l $44e.w,a0
	move.l #7999,d0
	
toto2:
	move.w #1,(a0)+
	move.w #1,(a0)+
	move.w #$0,(a0)+
	move.w #$0,(a0)+
	dbf d0,toto2

	
;boucle_quitter:
	
;	cmp.b	#$39,$fffffc02
;	bne.s boucle_quitter
;cconin gemdos tape une touche

	move.w	#1,-(a7)
	trap	#1
	addq.l #2,a7
	
	;On restaure la palette originale
	movem.l sauve_palette,d0-d7
	movem.l d0-d7,$FFFF8240

	move.l $44e.w,a0
	move.l #7999,d0
	
affiche_ecran2:	
	
	; On vide les bits se trouvant a l'adresse a0 et on incremente son pointeur de 4
	; octets .l = longword = DWORD.
	clr.l (a0)+

	;on effectue la boucle tant que d0 n'est pas inferieur a 0
	dbra d0,affiche_ecran2
	
;Affichage des greetings
	move.l	#greets,-(a7)
	move.w	#$09,-(a7)
	trap 	#1

	addq.l  #6,a7
	
;	move.w  #$700,$ff8240	 
boucle_quitter2:
	
;	cmp.b	#$39,$fffffc02
;	bne.s boucle_quitter2
;cconin tape une touche
	move.w	#1,-(a7)
	trap	#1
	addq.l	#2,a7
	
;restaure souris
	dc.w $a009

	move.l sauve_s,-(a7)
	move.w #SUPERVISEUR,-(a7)
	trap #BIOS
	addq.l #6,a7


	
	; Pterm0 on retourne au gem :D
	clr.l -(a7)
	trap #BIOS
	 


	section data
sauve_s	dc.l	0	; Reserve un DWORD initialise a 0
	even
;greets	dc.b 'toto',0
greets INCBIN greets.txt

	section bss
sauve_palette ds.l 8	; Reserve 8 DWORD ou 8 longword :)	
		
