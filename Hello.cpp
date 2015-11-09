/ * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =  
 c h a r a c t e r   m o v e m e n t   t e s t i n g   u s i n g   F l y 2  
  
 -   L o a d   a   s c e n e  
 -   G e n e r a t e   a   t e r r a i n   o b j e c t  
 -   L o a d   a   c h a r a c t e r  
 -   C o n t r o l   a   c h a r a c t e r   t o   m o v e  
 -   C h a n g e   p o s e s  
  
 ( C ) 2 0 1 2 - 2 0 1 5   C h u a n - C h a n g   W a n g ,   A l l   R i g h t s   R e s e r v e d  
 C r e a t e d   :   0 8 0 2 ,   2 0 1 2  
  
 L a s t   U p d a t e d   :   1 0 0 4 ,   2 0 1 5 ,   K e v i n   C .   W a n g  
 = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = * /  
 # i n c l u d e   " F l y W i n 3 2 . h "  
 # i n c l u d e   < m a t h . h >  
  
 V I E W P O R T i d   v I D ;                                   / /   t h e   m a j o r   v i e w p o r t  
 S C E N E i d   s I D ;                                         / /   t h e   3 D   s c e n e  
 O B J E C T i d   c I D ,   t I D ,   d u m m y O b j I D ;                             / /   t h e   m a i n   c a m e r a   a n d   t h e   t e r r a i n   f o r   t e r r a i n   f o l l o w i n g  
 C H A R A C T E R i d   a c t o r I D ;                         / /   t h e   m a j o r   c h a r a c t e r  
 A C T I O N i d   i d l e I D ,   r u n I D ,   c u r P o s e I D ;   / /   t w o   a c t i o n s  
 R O O M i d   t e r r a i n R o o m I D   =   F A I L E D _ I D ;  
 T E X T i d   t e x t I D   =   F A I L E D _ I D ;  
  
 / /   s o m e   g l o b a l s  
 i n t   f r a m e   =   0 ;  
 i n t   o l d X ,   o l d Y ,   o l d X M ,   o l d Y M ,   o l d X M M ,   o l d Y M M ;  
  
 / /   h o t k e y   c a l l b a c k s  
 v o i d   Q u i t G a m e ( B Y T E ,   B O O L 4 ) ;  
 v o i d   M o v e m e n t ( B Y T E ,   B O O L 4 ) ;  
  
 / /   t i m e r   c a l l b a c k s  
 v o i d   G a m e A I ( i n t ) ;  
 v o i d   R e n d e r I t ( i n t ) ;  
  
 / /   m o u s e   c a l l b a c k s  
 v o i d   I n i t P i v o t ( i n t ,   i n t ) ;  
 v o i d   P i v o t C a m ( i n t ,   i n t ) ;  
 v o i d   I n i t M o v e ( i n t ,   i n t ) ;  
 v o i d   M o v e C a m ( i n t ,   i n t ) ;  
 v o i d   I n i t Z o o m ( i n t ,   i n t ) ;  
 v o i d   Z o o m C a m ( i n t ,   i n t ) ;  
  
 v o i d   R o t a t e C a m ( i n t   x ,   i n t   y ) ;  
 v o i d   I n i t Z o o m 2 ( i n t ,   i n t ) ;  
 v o i d   Z o o m C a m 2 ( i n t ,   i n t ) ;  
  
 / / c a m e r a   c o n t r o l   p a r a m e t e r s  
 f l o a t   d i s t a n c e   =   7 0 0 ;  
 f l o a t   x S p e e d   =   1 0 ;  
 f l o a t   y S p e e d   =   1 0 ;  
  
 c o n s t   f l o a t   C a m e r a B a s e H e i g h t   =   3 0 0 ;  
  
 f l o a t   r o t _ x   =   0 ;  
 f l o a t   r o t _ y   =   - 3 0 ;  
  
 f l o a t   p l a y e r R o t _ x   =   0 ;  
  
 b o o l   I s C a m e r a F o l l o w   =   f a l s e ;  
  
 b o o l   l e f t _ f i r s t P r e s s e d   =   f a l s e ;  
 b o o l   r i g h t _ f i r s t P r e s s e d   =   f a l s e ;  
  
 b o o l   u p _ f i r s t P r e s s e d   =   f a l s e ;  
 b o o l   d o w n _ f i r s t P r e s s e d   =   f a l s e ;  
  
 f l o a t   r a d i u s   =   0 ;  
 f l o a t   d i s t   =   0 ;  
  
 f l o a t   c a m e r a H e i g h t   =   C a m e r a B a s e H e i g h t ;  
  
 / / c a m e r a  
 v o i d   C a m e r a C o n t r o l ( C H A R A C T E R i d   t a r g e t i d ) ;  
 v o i d   C a m e r a F o c u s ( C H A R A C T E R i d   t a r g e t i d ,   f l o a t   s c a l e r ) ;  
 v o i d   I n i t C a m e r a ( ) ;  
  
 / /   m a t h   h e l p e r   f u n c t i o n s  
 v o i d   E u l e r T o Q u a r t e r n i o n ( f l o a t   x ,   f l o a t   y ,   f l o a t   z ,   f l o a t *   r e s u l t ) ;  
 v o i d   Q u a t e r n i o n M u l t i V e c t o r ( f l o a t *   q u a t ,   f l o a t *   v e c ,   f l o a t *   r e s u l t ) ;  
 f l o a t   d e g T o R a d ( f l o a t   d ) ;  
 v o i d   V e c t o r C r o s s ( f l o a t *   v e c 1 ,   f l o a t *   v e c 2 ,   f l o a t *   r e s u l t ) ;  
 f l o a t   V e c t o r D o t ( f l o a t *   v e c 1 ,   f l o a t *   v e c 2 ,   f l o a t *   r e s u l t ) ;  
 v o i d   V e c t o r N o r m a l i z e ( f l o a t *   v e c 1 ,   f l o a t *   r e s u l t ) ;  
 f l o a t   V e c t o r M a g n i t u d e ( f l o a t *   v e c 1 ) ;  
 v o i d   V e c t o r S c a l e r M u l t i p l y ( f l o a t   s ,   f l o a t *   v e c 1 ,   f l o a t *   r e s u l t ) ;  
  
 / * - - - - - - - - - - - - - - - - - -  
 t h e   m a i n   p r o g r a m  
 C . W a n g   1 0 1 0 ,   2 0 1 4  
 - - - - - - - - - - - - - - - - - - - * /  
 v o i d   F y M a i n ( i n t   a r g c ,   c h a r   * * a r g v )  
 {  
 	 / /   c r e a t e   a   n e w   w o r l d  
 	 B O O L 4   b e O K   =   F y S t a r t F l y W i n 3 2 ( " N T U @ 2 0 1 4   H o m e w o r k   # 0 1   -   U s e   F l y 2 " ,   0 ,   0 ,   1 0 2 4 ,   7 6 8 ,   F A L S E ) ;  
  
 	 / /   s e t u p   t h e   d a t a   s e a r c h i n g   p a t h s  
 	 F y S e t S h a d e r P a t h ( " D a t a \ \ N T U 6 \ \ S h a d e r s " ) ;  
 	 F y S e t M o d e l P a t h ( " D a t a \ \ N T U 6 \ \ S c e n e s " ) ;  
 	 F y S e t T e x t u r e P a t h ( " D a t a \ \ N T U 6 \ \ S c e n e s \ \ T e x t u r e s " ) ;  
 	 F y S e t S c e n e P a t h ( " D a t a \ \ N T U 6 \ \ S c e n e s " ) ;  
  
 	 / /   c r e a t e   a   v i e w p o r t  
 	 v I D   =   F y C r e a t e V i e w p o r t ( 0 ,   0 ,   1 0 2 4 ,   7 6 8 ) ;  
 	 F n V i e w p o r t   v p ;  
 	 v p . I D ( v I D ) ;  
  
 	 / /   c r e a t e   a   3 D   s c e n e  
 	 s I D   =   F y C r e a t e S c e n e ( 1 0 ) ;  
 	 F n S c e n e   s c e n e ;  
 	 s c e n e . I D ( s I D ) ;  
  
 	 / /   l o a d   t h e   s c e n e  
 	 s c e n e . L o a d ( " g a m e S c e n e 0 2 " ) ;  
 	 s c e n e . S e t A m b i e n t L i g h t s ( 1 . 0 f ,   1 . 0 f ,   1 . 0 f ,   0 . 6 f ,   0 . 6 f ,   0 . 6 f ) ;  
  
 	 / /   l o a d   t h e   t e r r a i n  
 	 t I D   =   s c e n e . C r e a t e O b j e c t ( O B J E C T ) ;  
 	 F n O b j e c t   t e r r a i n ;  
 	 t e r r a i n . I D ( t I D ) ;  
 	 B O O L   b e O K 1   =   t e r r a i n . L o a d ( " t e r r a i n " ) ;  
 	 t e r r a i n . S h o w ( F A L S E ) ;  
  
 	 / /   s e t   t e r r a i n   e n v i r o n m e n t  
 	 t e r r a i n R o o m I D   =   s c e n e . C r e a t e R o o m ( S I M P L E _ R O O M ,   1 0 ) ;  
 	 F n R o o m   r o o m ;  
 	 r o o m . I D ( t e r r a i n R o o m I D ) ;  
 	 r o o m . A d d O b j e c t ( t I D ) ;  
  
 	 / /   l o a d   t h e   c h a r a c t e r  
 	 F y S e t M o d e l P a t h ( " D a t a \ \ N T U 6 \ \ C h a r a c t e r s " ) ;  
 	 F y S e t T e x t u r e P a t h ( " D a t a \ \ N T U 6 \ \ C h a r a c t e r s " ) ;  
 	 F y S e t C h a r a c t e r P a t h ( " D a t a \ \ N T U 6 \ \ C h a r a c t e r s " ) ;  
 	 a c t o r I D   =   s c e n e . L o a d C h a r a c t e r ( " L y u b u 2 " ) ;  
  
 	 / /   p u t   t h e   c h a r a c t e r   o n   t e r r a i n  
 	 f l o a t   p o s [ 3 ] ,   f D i r [ 3 ] ,   u D i r [ 3 ] ;  
 	 F n C h a r a c t e r   a c t o r ;  
 	 a c t o r . I D ( a c t o r I D ) ;  
 	 p o s [ 0 ]   =   3 5 6 9 . 0 f ;   p o s [ 1 ]   =   - 3 2 0 8 . 0 f ;   p o s [ 2 ]   =   1 0 0 0 . 0 f ;  
 	 f D i r [ 0 ]   =   1 . 0 f ;   f D i r [ 1 ]   =   - 1 . 0 f ;   f D i r [ 2 ]   =   0 . 0 f ;  
 	 u D i r [ 0 ]   =   0 . 0 f ;   u D i r [ 1 ]   =   0 . 0 f ;   u D i r [ 2 ]   =   1 . 0 f ;  
 	 a c t o r . S e t D i r e c t i o n ( f D i r ,   u D i r ) ;  
  
 	 a c t o r . S e t T e r r a i n R o o m ( t e r r a i n R o o m I D ,   1 0 . 0 f ) ;  
 	 b e O K   =   a c t o r . P u t O n T e r r a i n ( p o s ) ;  
  
 	 / /   G e t   t w o   c h a r a c t e r   a c t i o n s   p r e - d e f i n e d   a t   L y u b u 2  
 	 i d l e I D   =   a c t o r . G e t B o d y A c t i o n ( N U L L ,   " I d l e " ) ;  
 	 r u n I D   =   a c t o r . G e t B o d y A c t i o n ( N U L L ,   " R u n " ) ;  
  
 	 / /   s e t   t h e   c h a r a c t e r   t o   i d l e   a c t i o n  
 	 c u r P o s e I D   =   i d l e I D ;  
 	 a c t o r . S e t C u r r e n t A c t i o n ( N U L L ,   0 ,   c u r P o s e I D ) ;  
 	 a c t o r . P l a y ( S T A R T ,   0 . 0 f ,   F A L S E ,   T R U E ) ;  
 	 a c t o r . T u r n R i g h t ( 9 0 . 0 f ) ;  
  
 	 / /   t r a n s l a t e   t h e   c a m e r a  
 	 c I D   =   s c e n e . C r e a t e O b j e c t ( C A M E R A ) ;  
 	 F n C a m e r a   c a m e r a ;  
 	 c a m e r a . I D ( c I D ) ;  
 	 c a m e r a . S e t N e a r P l a n e ( 5 . 0 f ) ;  
 	 c a m e r a . S e t F a r P l a n e ( 1 0 0 0 0 0 . 0 f ) ;  
  
 	 d u m m y O b j I D   =   s c e n e . C r e a t e O b j e c t ( O B J E C T ) ;  
  
  
 	 / /   s e t   c a m e r a   i n i t i a l   p o s i t i o n   a n d   o r i e n t a t i o n  
 	 p o s [ 0 ]   =   4 0 6 9 . 0 f ;   p o s [ 1 ]   =   - 3 2 0 8 . 0 f ;   p o s [ 2 ]   =   9 3 . 0 4 6 f ;  
 	 f D i r [ 0 ]   =   - 5 0 0 . 0 f ;   f D i r [ 1 ]   =   - 0 . 0 f ;   f D i r [ 2 ]   =   - 0 . 0 f ;  
 	 u D i r [ 0 ]   =   - 0 . 1 1 6 f ;   u D i r [ 1 ]   =   - 0 . 0 3 1 f ;   u D i r [ 2 ]   =   0 . 9 9 3 f ;  
 	 c a m e r a . S e t P o s i t i o n ( p o s ) ;  
 	 c a m e r a . S e t D i r e c t i o n ( f D i r ,   u D i r ) ;  
  
 	 f l o a t   m a i n L i g h t P o s [ 3 ]   =   {   - 4 5 7 9 . 0 ,   - 7 1 4 . 0 ,   1 5 5 3 0 . 0   } ;  
 	 f l o a t   m a i n L i g h t F D i r [ 3 ]   =   {   0 . 2 7 6 ,   0 . 0 ,   - 0 . 9 6 1   } ;  
 	 f l o a t   m a i n L i g h t U D i r [ 3 ]   =   {   0 . 9 6 1 ,   0 . 0 2 6 ,   0 . 2 7 6   } ;  
  
 	 F n L i g h t   l g t ;  
 	 l g t . I D ( s c e n e . C r e a t e O b j e c t ( L I G H T ) ) ;  
 	 l g t . T r a n s l a t e ( m a i n L i g h t P o s [ 0 ] ,   m a i n L i g h t P o s [ 1 ] ,   m a i n L i g h t P o s [ 2 ] ,   R E P L A C E ) ;  
 	 l g t . S e t D i r e c t i o n ( m a i n L i g h t F D i r ,   m a i n L i g h t U D i r ) ;  
 	 l g t . S e t L i g h t T y p e ( P A R A L L E L _ L I G H T ) ;  
 	 l g t . S e t C o l o r ( 1 . 0 f ,   1 . 0 f ,   1 . 0 f ) ;  
 	 l g t . S e t N a m e ( " M a i n L i g h t " ) ;  
 	 l g t . S e t I n t e n s i t y ( 0 . 4 f ) ;  
  
 	 / /   c r e a t e   a   t e x t   o b j e c t   f o r   d i s p l a y i n g   m e s s a g e s   o n   s c r e e n  
 	 t e x t I D   =   F y C r e a t e T e x t ( " T r e b u c h e t   M S " ,   1 8 ,   F A L S E ,   F A L S E ) ;  
  
 	 / /   s e t   H o t k e y s  
 	 F y D e f i n e H o t K e y ( F Y _ E S C A P E ,   Q u i t G a m e ,   F A L S E ) ;     / /   e s c a p e   f o r   q u i t i n g   t h e   g a m e  
 	 F y D e f i n e H o t K e y ( F Y _ U P ,   M o v e m e n t ,   F A L S E ) ;             / /   U p   f o r   m o v i n g   f o r w a r d  
 	 F y D e f i n e H o t K e y ( F Y _ D O W N ,   M o v e m e n t ,   F A L S E ) ;             / /   D o w n   f o r   m o v i n g   b a c k w a r d  
 	 F y D e f i n e H o t K e y ( F Y _ R I G H T ,   M o v e m e n t ,   F A L S E ) ;       / /   R i g h t   f o r   t u r n i n g   r i g h t  
 	 F y D e f i n e H o t K e y ( F Y _ L E F T ,   M o v e m e n t ,   F A L S E ) ;         / /   L e f t   f o r   t u r n i n g   l e f t  
  
 	 / /   d e f i n e   s o m e   m o u s e   f u n c t i o n s  
 	 i f   ( ! I s C a m e r a F o l l o w )  
 	 {  
 	 	 F y B i n d M o u s e F u n c t i o n ( L E F T _ M O U S E ,   I n i t P i v o t ,   P i v o t C a m ,   N U L L ,   N U L L ) ;  
 	 	 F y B i n d M o u s e F u n c t i o n ( M I D D L E _ M O U S E ,   I n i t Z o o m ,   Z o o m C a m ,   N U L L ,   N U L L ) ;  
 	 	 F y B i n d M o u s e F u n c t i o n ( R I G H T _ M O U S E ,   I n i t M o v e ,   M o v e C a m ,   N U L L ,   N U L L ) ;  
 	 }  
 	 e l s e  
 	 {  
 	 	 F y B i n d M o u s e F u n c t i o n ( L E F T _ M O U S E ,   I n i t Z o o m 2 ,   Z o o m C a m 2 ,   N U L L ,   N U L L ) ;  
 	 	 F y B i n d M o u s e F u n c t i o n ( R I G H T _ M O U S E ,   N U L L ,   R o t a t e C a m ,   N U L L ,   N U L L ) ;  
 	 }  
  
 	 C a m e r a F o c u s ( a c t o r I D ,   1 ) ;  
  
 	 / /   b i n d   t i m e r s ,   f r a m e   r a t e   =   3 0   f p s  
 	 F y B i n d T i m e r ( 0 ,   3 0 . 0 f ,   G a m e A I ,   T R U E ) ;  
 	 F y B i n d T i m e r ( 1 ,   3 0 . 0 f ,   R e n d e r I t ,   T R U E ) ;  
  
 	 / /   i n v o k e   t h e   s y s t e m  
 	 F y I n v o k e F l y ( T R U E ) ;  
  
 	  
 }  
  
 / / � � � � � � � � � o � �  
 v o i d   I n i t C a m e r a ( )  
 {  
 	 F n C a m e r a   c a m e r a ;  
 	 c a m e r a . I D ( c I D ) ;  
  
 	 F n C h a r a c t e r   a c t o r ;  
 	 a c t o r . I D ( a c t o r I D ) ;  
  
 	 f l o a t   p l a y e r F D i r [ 3 ] ,   t a r g e t P o s [ 3 ] ,   p l a y e r U D i r [ 3 ] ;  
 	 a c t o r . G e t P o s i t i o n ( t a r g e t P o s ) ;  
 	 a c t o r . G e t D i r e c t i o n ( p l a y e r F D i r ,   p l a y e r U D i r ) ;  
  
 	 f l o a t   c a m L o c a l P o s [ 3 ] ,   c a m e r a P o s [ 3 ] ,   c a m e r a F o r w a r d [ 3 ] ;  
 	 c a m L o c a l P o s [ 0 ]   =   - 1 * d i s t a n c e * p l a y e r F D i r [ 0 ] ;  
 	 c a m L o c a l P o s [ 1 ]   =   - 1 * d i s t a n c e * p l a y e r F D i r [ 1 ] ;  
 	 c a m L o c a l P o s [ 2 ]   =   c a m e r a H e i g h t ;  
  
 	 F n O b j e c t   c o n t r o l O b j ;  
 	 c o n t r o l O b j . I D ( d u m m y O b j I D ) ;  
 	 c o n t r o l O b j . S e t P o s i t i o n ( t a r g e t P o s ) ;  
 	 c o n t r o l O b j . S e t D i r e c t i o n ( p l a y e r F D i r ,   p l a y e r U D i r ) ;  
  
 	 c a m e r a . S e t P a r e n t ( d u m m y O b j I D ) ;  
 	 c a m e r a . S e t P o s i t i o n ( c a m L o c a l P o s ,   f a l s e ) ;  
  
 	 c a m e r a . G e t P o s i t i o n ( c a m e r a P o s ) ;  
 	 c a m e r a F o r w a r d [ 0 ]   =   t a r g e t P o s [ 0 ]   -   c a m e r a P o s [ 0 ] ;  
 	 c a m e r a F o r w a r d [ 1 ]   =   t a r g e t P o s [ 1 ]   -   c a m e r a P o s [ 1 ] ;  
 	 c a m e r a F o r w a r d [ 2 ]   =   t a r g e t P o s [ 2 ]   -   c a m e r a P o s [ 2 ] ;  
  
 	 f l o a t   p l a y e r R i g h t [ 3 ] ;  
 	 V e c t o r C r o s s ( c a m e r a F o r w a r d ,   p l a y e r U D i r ,   p l a y e r R i g h t ) ;  
 	 f l o a t   c a m U p D i r [ 3 ] ;  
 	 V e c t o r C r o s s ( p l a y e r R i g h t ,   c a m e r a F o r w a r d ,   c a m U p D i r ) ;  
  
 	 c a m e r a . S e t D i r e c t i o n ( c a m e r a F o r w a r d ,   c a m U p D i r ) ;  
 }  
  
 / / c a m e r a   o r b i t   c o n t r o l  
 v o i d   C a m e r a C o n t r o l ( C H A R A C T E R i d   t a r g e t i d )  
 {  
 	 F n C a m e r a   c a m e r a ;  
 	 c a m e r a . I D ( c I D ) ;  
  
 	 F n C h a r a c t e r   a c t o r ;  
 	 a c t o r . I D ( t a r g e t i d ) ;  
  
 	 f l o a t   t a r g e t P o s [ 3 ] ;  
 	 a c t o r . G e t P o s i t i o n ( t a r g e t P o s ) ;  
  
 	 f l o a t   n e g a t i v e D i s t a n c e [ 3 ] ;  
 	 n e g a t i v e D i s t a n c e [ 0 ]   =   - d i s t a n c e ;  
 	 n e g a t i v e D i s t a n c e [ 1 ]   =   0 ;  
 	 n e g a t i v e D i s t a n c e [ 2 ]   =   0 ;  
  
 	 f l o a t   r o t a t i o n [ 3 ] ;  
 	 E u l e r T o Q u a r t e r n i o n ( 0 ,   d e g T o R a d ( r o t _ y ) ,   d e g T o R a d ( r o t _ x ) ,   r o t a t i o n ) ;  
  
 	 f l o a t   f o r w a r d D i r [ 3 ] ;  
 	 Q u a t e r n i o n M u l t i V e c t o r ( r o t a t i o n ,   n e g a t i v e D i s t a n c e ,   f o r w a r d D i r ) ;  
  
 	 f l o a t   c a m P o s [ 3 ] ,   G l o b a l R i g h t [ 3 ] ;  
 	 G l o b a l R i g h t [ 0 ]   =   0 ;  
 	 G l o b a l R i g h t [ 1 ]   =   1 ;  
 	 G l o b a l R i g h t [ 2 ]   =   0 ;  
  
  
 	 c a m P o s [ 0 ]   =   t a r g e t P o s [ 0 ]   -   f o r w a r d D i r [ 0 ] ;  
 	 c a m P o s [ 1 ]   =   t a r g e t P o s [ 1 ]   -   f o r w a r d D i r [ 1 ] ;  
 	 c a m P o s [ 2 ]   =   t a r g e t P o s [ 2 ]   -   f o r w a r d D i r [ 2 ] ;  
  
 	 f l o a t   u p D i r [ 3 ] ;  
 	 V e c t o r C r o s s ( G l o b a l R i g h t ,   f o r w a r d D i r ,   u p D i r ) ;  
  
 	 / / c a m e r a . Q u a t e r n i o n ( r o t a t i o n [ 0 ] ,   r o t a t i o n [ 1 ] ,   r o t a t i o n [ 2 ] ,   r o t a t i o n [ 3 ] ,   G L O B A L ) ;  
 	 c a m e r a . S e t P o s i t i o n ( c a m P o s ) ;  
 	 c a m e r a . S e t D i r e c t i o n ( f o r w a r d D i r ,   u p D i r ) ;  
 }  
  
 v o i d   C a m e r a F o c u s ( C H A R A C T E R i d   t a r g e t i d ,   f l o a t   s c a l e r )  
 {  
 	 F n C a m e r a   c a m e r a ;  
 	 c a m e r a . I D ( c I D ) ;  
  
 	 F n C h a r a c t e r   a c t o r ;  
 	 a c t o r . I D ( t a r g e t i d ) ;  
  
 	 f l o a t   t a r g e t P o s [ 3 ] ;  
 	 a c t o r . G e t P o s i t i o n ( t a r g e t P o s ) ;  
  
 	 f l o a t   f D i r [ 3 ] ,   u p D i r [ 3 ] , c a m P o s [ 3 ] , c a m e r a P o s [ 3 ] , c a m e r a F o r w a r d [ 3 ] ;  
 	 a c t o r . G e t D i r e c t i o n ( f D i r ,   u p D i r ) ;  
 	 c a m e r a . G e t P o s i t i o n ( c a m e r a P o s ) ;  
  
 	 c a m e r a F o r w a r d [ 0 ]   =   d i s t a n c e * s c a l e r * f D i r [ 0 ] ;  
 	 c a m e r a F o r w a r d [ 1 ]   =   d i s t a n c e * s c a l e r * f D i r [ 1 ] ;  
 	 c a m e r a F o r w a r d [ 2 ]   =   - c a m e r a H e i g h t ;  
  
 	 f l o a t   r i g h t D i r [ 3 ] ;  
 	 V e c t o r C r o s s ( c a m e r a F o r w a r d ,   u p D i r ,   r i g h t D i r ) ;  
  
 	 f l o a t   c a m U p D i r [ 3 ] ;  
 	 V e c t o r C r o s s ( r i g h t D i r ,   c a m e r a F o r w a r d ,   c a m U p D i r ) ;  
  
 	 c a m P o s [ 0 ]   =   t a r g e t P o s [ 0 ]   -   c a m e r a F o r w a r d [ 0 ] ;  
 	 c a m P o s [ 1 ]   =   t a r g e t P o s [ 1 ]   -   c a m e r a F o r w a r d [ 1 ] ;  
 	 c a m P o s [ 2 ]   =   t a r g e t P o s [ 2 ]   -   c a m e r a F o r w a r d [ 2 ] ;  
  
 	 c a m e r a . S e t D i r e c t i o n ( c a m e r a F o r w a r d ,   c a m U p D i r ) ;  
 	 c a m e r a . S e t P o s i t i o n ( c a m P o s ) ;  
 }  
  
 f l o a t   l a s t P l a y e r P o s [ 3 ] ;  
  
 / * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  
 3 0 f p s   t i m e r   c a l l b a c k   i n   f i x e d   f r a m e   r a t e   f o r   m a j o r   g a m e   l o o p  
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - * /  
 v o i d   G a m e A I ( i n t   s k i p )  
 {  
 	 F n C h a r a c t e r   a c t o r ;  
  
 	 / /   p l a y   c h a r a c t e r   p o s e  
 	 a c t o r . I D ( a c t o r I D ) ;  
 	 a c t o r . P l a y ( L O O P ,   ( f l o a t ) s k i p ,   F A L S E ,   T R U E ) ;  
  
 	 F n O b j e c t   c o n t r o l O b j ;  
 	 c o n t r o l O b j . I D ( d u m m y O b j I D ) ;  
  
 	 F n C a m e r a   c a m e r a ;  
 	 c a m e r a . I D ( c I D ) ;  
  
 	 f l o a t   f D i r [ 3 ] ,   u D i r [ 3 ] ;  
 	 f l o a t   p l a y e r P o s [ 3 ] , d u m m y P o s [ 3 ] ;  
 	 a c t o r . G e t P o s i t i o n ( p l a y e r P o s ) ;  
 	 a c t o r . G e t D i r e c t i o n ( f D i r ,   u D i r ) ;  
  
 	 f l o a t   c a m e r a P o s [ 3 ] ;  
 	 c a m e r a . G e t P o s i t i o n ( c a m e r a P o s ) ;  
  
 	 f l o a t   f o r w a r d D i r [ 3 ] ,   b a c k w a r d D i r [ 3 ] ,   c a m F o r w a r d D i r [ 3 ] ;  
  
 	 c a m F o r w a r d D i r [ 0 ]   =   p l a y e r P o s [ 0 ]   -   c a m e r a P o s [ 0 ] ;  
 	 c a m F o r w a r d D i r [ 1 ]   =   p l a y e r P o s [ 1 ]   -   c a m e r a P o s [ 1 ] ;  
 	 c a m F o r w a r d D i r [ 2 ]   =   p l a y e r P o s [ 2 ]   -   c a m e r a P o s [ 2 ] ;  
  
 	 f o r w a r d D i r [ 0 ]   =   c a m F o r w a r d D i r [ 0 ] ;  
 	 f o r w a r d D i r [ 1 ]   =   c a m F o r w a r d D i r [ 1 ] ;  
 	 f o r w a r d D i r [ 2 ]   =   0 ;  
  
 	 b a c k w a r d D i r [ 0 ]   =   - f o r w a r d D i r [ 0 ] ;  
 	 b a c k w a r d D i r [ 1 ]   =   - f o r w a r d D i r [ 1 ] ;  
 	 b a c k w a r d D i r [ 2 ]   =   0 ;  
  
 	 F n O b j e c t   t e r r a i n ;  
 	 t e r r a i n . I D ( t I D ) ;  
  
 	 f l o a t   h i t P o s [ 3 ] ,   h i t D i r [ 3 ] ,   G l o b a l D o w n D i r [ 3 ] ;  
  
 	 G l o b a l D o w n D i r [ 0 ]   =   0 ;  
 	 G l o b a l D o w n D i r [ 1 ]   =   0 ;  
 	 G l o b a l D o w n D i r [ 2 ]   =   - 1 ;  
  
 	 f l o a t   h i t   =   t e r r a i n . H i t T e s t ( c a m e r a P o s ,   G l o b a l D o w n D i r ,   h i t P o s ) ;  
 	 i f   ( h i t   >   0 )  
 	 {  
 	 	 d i s t a n c e   + =   1 0 ;  
 	 	 c a m e r a H e i g h t   - =   1 0 ;  
  
 	 	 i f   ( d i s t a n c e   >   7 0 0 )  
 	 	 	 d i s t a n c e   =   7 0 0 ;  
  
 	 	 i f   ( c a m e r a H e i g h t   <   C a m e r a B a s e H e i g h t )  
 	 	           c a m e r a H e i g h t   =   C a m e r a B a s e H e i g h t ;  
 	 }  
 	 e l s e  
 	 {  
 	 	 d i s t a n c e   - =   1 0 ;  
 	 	 i f   ( d i s t a n c e   <   1 0 )  
 	 	 	 d i s t a n c e   =   1 0 ;  
 	 	 c a m e r a H e i g h t   + =   1 0 ;  
  
 	 	 i f   ( c a m e r a H e i g h t   >   1 0 0 0 )  
 	 	 	 c a m e r a H e i g h t   =   1 0 0 0 ;  
 	 }  
  
 	 i f   ( F y C h e c k H o t K e y S t a t u s ( F Y _ U P ) )  
 	 {  
 	 	 i f   ( ! u p _ f i r s t P r e s s e d )  
 	 	 {  
 	 	 	 f l o a t   p l a y e r F o r w a r d [ 3 ] ;  
 	 	 	 p l a y e r F o r w a r d [ 0 ]   =   f o r w a r d D i r [ 0 ] ;  
 	 	 	 p l a y e r F o r w a r d [ 1 ]   =   f o r w a r d D i r [ 1 ] ;  
 	 	 	 p l a y e r F o r w a r d [ 2 ]   =   f o r w a r d D i r [ 2 ] ;  
  
 	 	 	 a c t o r . S e t D i r e c t i o n ( p l a y e r F o r w a r d ,   u D i r ) ;  
 	 	 	 u p _ f i r s t P r e s s e d   =   t r u e ;  
 	 	 }  
  
 	 	 a c t o r . M o v e F o r w a r d ( 2 0 , t r u e , t r u e , 0 , t r u e ) ;  
  
 	 	 / / c o n t r o l O b j . S e t P o s i t i o n ( p l a y e r P o s ) ;  
 	 	 C a m e r a F o c u s ( a c t o r I D , 1 ) ;  
  
 	 }  
 	 e l s e   i f   ( F y C h e c k H o t K e y S t a t u s ( F Y _ D O W N ) )  
 	 {  
 	 	 i f   ( ! d o w n _ f i r s t P r e s s e d )  
 	 	 {  
 	 	 	 f l o a t   p l a y e r F o r w a r d [ 3 ] ;  
 	 	 	 p l a y e r F o r w a r d [ 0 ]   =   b a c k w a r d D i r [ 0 ] ;  
 	 	 	 p l a y e r F o r w a r d [ 1 ]   =   b a c k w a r d D i r [ 1 ] ;  
 	 	 	 p l a y e r F o r w a r d [ 2 ]   =   b a c k w a r d D i r [ 2 ] ;  
  
 	 	 	 a c t o r . S e t D i r e c t i o n ( p l a y e r F o r w a r d ,   u D i r ) ;  
 	 	 	 d o w n _ f i r s t P r e s s e d   =   t r u e ;  
 	 	 }  
  
 	 	 a c t o r . M o v e F o r w a r d ( 2 0 ,   t r u e ,   t r u e ,   0 ,   t r u e ) ;  
  
 	 	 / / c o n t r o l O b j . S e t P o s i t i o n ( p l a y e r P o s ) ;  
 	 	 C a m e r a F o c u s ( a c t o r I D , - 1 ) ;  
 	 }  
 	 e l s e   i f   ( F y C h e c k H o t K e y S t a t u s ( F Y _ L E F T ) )  
 	 {  
 	 	 I s C a m e r a F o l l o w   =   f a l s e ;  
  
 	 	 i f   ( ! l e f t _ f i r s t P r e s s e d )  
 	 	 {  
 	 	 	 f l o a t   p l a y e r F o r w a r d [ 3 ] ;  
 	 	 	 V e c t o r C r o s s ( b a c k w a r d D i r ,   u D i r ,   p l a y e r F o r w a r d ) ;  
 	 	 	 a c t o r . S e t D i r e c t i o n ( p l a y e r F o r w a r d ,   u D i r ) ;  
  
 	 	 	 r a d i u s   =   s q r t ( f o r w a r d D i r [ 0 ]   *   f o r w a r d D i r [ 0 ]   +   f o r w a r d D i r [ 1 ]   *   f o r w a r d D i r [ 1 ] ) ;  
 	 	 	 d i s t   =   r a d i u s * d e g T o R a d ( 2 ) ;  
  
 	 	 	 l e f t _ f i r s t P r e s s e d   =   t r u e ;  
 	 	 }  
  
 	 	  
 	 	 a c t o r . M o v e F o r w a r d ( d i s t ,   t r u e ,   t r u e ,   0 ,   t r u e ) ;  
 	 	  
 	 	 f l o a t   p l a y e r F [ 3 ] ,   p l a y e r U [ 3 ] ;  
 	 	 a c t o r . G e t D i r e c t i o n ( p l a y e r F ,   p l a y e r U ) ;  
  
 	 	 f l o a t   r a d i u s D i r [ 3 ] ;  
 	 	 V e c t o r C r o s s ( p l a y e r U ,   p l a y e r F ,   r a d i u s D i r ) ;  
  
 	 	 f l o a t   c a m P o s [ 3 ] ;  
 	 	 c a m P o s [ 0 ]   =   p l a y e r P o s [ 0 ]   +   d i s t a n c e * r a d i u s D i r [ 0 ] ;  
 	 	 c a m P o s [ 1 ]   =   p l a y e r P o s [ 1 ]   +   d i s t a n c e * r a d i u s D i r [ 1 ] ;  
 	 	 c a m P o s [ 2 ]   =   p l a y e r P o s [ 2 ]   +   c a m e r a H e i g h t ;  
 	 	 c a m e r a . S e t P o s i t i o n ( c a m P o s ) ;  
  
 	 	 f l o a t   c a m U p D i r [ 3 ] ;  
 	 	 V e c t o r C r o s s ( c a m F o r w a r d D i r ,   p l a y e r F ,   c a m U p D i r ) ;  
  
 	 	 f l o a t   d e l t a P o s [ 3 ] ;  
 	 	 d e l t a P o s [ 0 ]   =   p l a y e r P o s [ 0 ]   -   l a s t P l a y e r P o s [ 0 ] ;  
 	 	 d e l t a P o s [ 1 ]   =   p l a y e r P o s [ 1 ]   -   l a s t P l a y e r P o s [ 1 ] ;  
 	 	 d e l t a P o s [ 2 ]   =   p l a y e r P o s [ 2 ]   -   l a s t P l a y e r P o s [ 2 ] ;  
  
 	 	 f l o a t   m a g   =   V e c t o r M a g n i t u d e ( d e l t a P o s ) ;  
  
 	 	 / / i f   ( m a g   >   0 . 1 )  
 	 	 / / {  
 	 	 	 a c t o r . T u r n R i g h t ( - 2 ) ;  
 	 	 	 c a m e r a . S e t D i r e c t i o n ( c a m F o r w a r d D i r ,   c a m U p D i r ) ;  
 	 	 / / }  
  
 	 	 l a s t P l a y e r P o s [ 0 ]   =   p l a y e r P o s [ 0 ] ;  
 	 	 l a s t P l a y e r P o s [ 1 ]   =   p l a y e r P o s [ 1 ] ;  
 	 	 l a s t P l a y e r P o s [ 2 ]   =   p l a y e r P o s [ 2 ] ;  
  
 	 }  
 	  
 	 e l s e   i f   ( F y C h e c k H o t K e y S t a t u s ( F Y _ R I G H T ) )  
 	 {  
 	 	 I s C a m e r a F o l l o w   =   f a l s e ;  
 	 	 i f   ( ! r i g h t _ f i r s t P r e s s e d )  
 	 	 {  
 	 	 	 f l o a t   p l a y e r F o r w a r d [ 3 ] ;  
 	 	 	 V e c t o r C r o s s ( f o r w a r d D i r ,   u D i r ,   p l a y e r F o r w a r d ) ;  
 	 	 	 a c t o r . S e t D i r e c t i o n ( p l a y e r F o r w a r d ,   u D i r ) ;  
  
 	 	 	 r a d i u s   =   s q r t ( f o r w a r d D i r [ 0 ]   *   f o r w a r d D i r [ 0 ]   +   f o r w a r d D i r [ 1 ]   *   f o r w a r d D i r [ 1 ] ) ;  
 	 	 	 d i s t   =   r a d i u s * d e g T o R a d ( 2 ) ;  
  
 	 	 	 r i g h t _ f i r s t P r e s s e d   =   t r u e ;  
 	 	 }  
  
 	 	 a c t o r . M o v e F o r w a r d ( d i s t ,   t r u e ,   t r u e ,   0 ,   t r u e ) ;  
  
 	 	 f l o a t   p l a y e r F [ 3 ] ,   p l a y e r U [ 3 ] ;  
 	 	 a c t o r . G e t D i r e c t i o n ( p l a y e r F ,   p l a y e r U ) ;  
  
 	 	 f l o a t   r a d i u s D i r [ 3 ] ;  
 	 	 V e c t o r C r o s s ( p l a y e r F ,   p l a y e r U ,   r a d i u s D i r ) ;  
  
 	 	 f l o a t   c a m P o s [ 3 ] ;  
 	 	 c a m P o s [ 0 ]   =   p l a y e r P o s [ 0 ]   +   d i s t a n c e * r a d i u s D i r [ 0 ] ;  
 	 	 c a m P o s [ 1 ]   =   p l a y e r P o s [ 1 ]   +   d i s t a n c e * r a d i u s D i r [ 1 ] ;  
 	 	 c a m P o s [ 2 ]   =   p l a y e r P o s [ 2 ]   +   c a m e r a H e i g h t ;  
 	 	 c a m e r a . S e t P o s i t i o n ( c a m P o s ) ;  
  
  
 	 	 f l o a t   c a m U p D i r [ 3 ] ;  
 	 	 V e c t o r C r o s s ( p l a y e r F ,   c a m F o r w a r d D i r ,   c a m U p D i r ) ;  
  
 	 	 f l o a t   d e l t a P o s [ 3 ] ;  
 	 	 d e l t a P o s [ 0 ]   =   p l a y e r P o s [ 0 ]   -   l a s t P l a y e r P o s [ 0 ] ;  
 	 	 d e l t a P o s [ 1 ]   =   p l a y e r P o s [ 1 ]   -   l a s t P l a y e r P o s [ 1 ] ;  
 	 	 d e l t a P o s [ 2 ]   =   p l a y e r P o s [ 2 ]   -   l a s t P l a y e r P o s [ 2 ] ;  
  
 	 	 f l o a t   m a g   =   V e c t o r M a g n i t u d e ( d e l t a P o s ) ;  
  
 	 	 / / i f   ( m a g   >   0 . 1 )  
 	 	 / / {  
 	 	 	 a c t o r . T u r n R i g h t ( 2 ) ;  
 	 	 	 c a m e r a . S e t D i r e c t i o n ( c a m F o r w a r d D i r ,   c a m U p D i r ) ;  
 	 	 / / }  
  
 	 	 l a s t P l a y e r P o s [ 0 ]   =   p l a y e r P o s [ 0 ] ;  
 	 	 l a s t P l a y e r P o s [ 1 ]   =   p l a y e r P o s [ 1 ] ;  
 	 	 l a s t P l a y e r P o s [ 2 ]   =   p l a y e r P o s [ 2 ] ;  
  
 	 }  
 	 / / e l s e   { }  
 	 / /   . . . .  
 	 i f   ( I s C a m e r a F o l l o w )  
 	 {  
 	 	 C a m e r a C o n t r o l ( a c t o r I D ) ;  
 	 }  
 }  
  
  
 / * - - - - - - - - - - - - - - - - - - - - - -  
 p e r f o r m   t h e   r e n d e r i n g  
 C . W a n g   0 7 2 0 ,   2 0 0 6  
 - - - - - - - - - - - - - - - - - - - - - - - * /  
 v o i d   R e n d e r I t ( i n t   s k i p )  
 {  
 	 F n V i e w p o r t   v p ;  
  
 	 / /   r e n d e r   t h e   w h o l e   s c e n e  
 	 v p . I D ( v I D ) ;  
 	 v p . R e n d e r 3 D ( c I D ,   T R U E ,   T R U E ) ;  
  
 	 / /   g e t   c a m e r a ' s   d a t a  
 	 F n C a m e r a   c a m e r a ;  
 	 c a m e r a . I D ( c I D ) ;  
  
 	 f l o a t   p o s [ 3 ] ,   f D i r [ 3 ] ,   u D i r [ 3 ] ;  
 	 c a m e r a . G e t P o s i t i o n ( p o s ) ;  
 	 c a m e r a . G e t D i r e c t i o n ( f D i r ,   u D i r ) ;  
  
 	 / /   s h o w   f r a m e   r a t e  
 	 s t a t i c   c h a r   s t r i n g [ 1 2 8 ] ;  
 	 i f   ( f r a m e   = =   0 )   {  
 	 	 F y T i m e r R e s e t ( 0 ) ;  
 	 }  
  
 	 i f   ( f r a m e   /   1 0   *   1 0   = =   f r a m e )   {  
 	 	 f l o a t   c u r T i m e ;  
  
 	 	 c u r T i m e   =   F y T i m e r C h e c k T i m e ( 0 ) ;  
 	 	 s p r i n t f ( s t r i n g ,   " F p s :   % 6 . 2 f " ,   f r a m e   /   c u r T i m e ) ;  
 	 }  
  
 	 f r a m e   + =   s k i p ;  
 	 i f   ( f r a m e   > =   1 0 0 0 )   {  
 	 	 f r a m e   =   0 ;  
 	 }  
  
 	 F n T e x t   t e x t ;  
 	 t e x t . I D ( t e x t I D ) ;  
  
 	 t e x t . B e g i n ( v I D ) ;  
 	 t e x t . W r i t e ( s t r i n g ,   2 0 ,   2 0 ,   2 5 5 ,   0 ,   0 ) ;  
  
 	 c h a r   p o s S [ 2 5 6 ] ,   f D i r S [ 2 5 6 ] ,   u D i r S [ 2 5 6 ] ;  
 	 s p r i n t f ( p o s S ,   " p o s :   % 8 . 3 f   % 8 . 3 f   % 8 . 3 f " ,   p o s [ 0 ] ,   p o s [ 1 ] ,   p o s [ 2 ] ) ;  
 	 s p r i n t f ( f D i r S ,   " f a c i n g :   % 8 . 3 f   % 8 . 3 f   % 8 . 3 f " ,   f D i r [ 0 ] ,   f D i r [ 1 ] ,   f D i r [ 2 ] ) ;  
 	 s p r i n t f ( u D i r S ,   " u p :   % 8 . 3 f   % 8 . 3 f   % 8 . 3 f " ,   u D i r [ 0 ] ,   u D i r [ 1 ] ,   u D i r [ 2 ] ) ;  
  
 	 t e x t . W r i t e ( p o s S ,   2 0 ,   3 5 ,   2 5 5 ,   2 5 5 ,   0 ) ;  
 	 t e x t . W r i t e ( f D i r S ,   2 0 ,   5 0 ,   2 5 5 ,   2 5 5 ,   0 ) ;  
 	 t e x t . W r i t e ( u D i r S ,   2 0 ,   6 5 ,   2 5 5 ,   2 5 5 ,   0 ) ;  
  
 	 t e x t . E n d ( ) ;  
  
 	 / /   s w a p   b u f f e r  
 	 F y S w a p B u f f e r s ( ) ;  
 }  
  
 f l o a t   d e g T o R a d ( f l o a t   d )  
 {  
 	 r e t u r n   d * 3 . 1 4 1 5 9 f   /   1 8 0 ;  
 }  
  
 v o i d   E u l e r T o Q u a r t e r n i o n ( f l o a t   x ,   f l o a t   y ,   f l o a t   z ,   f l o a t *   q u a r t e r n i o n )   {  
 	 / /   A s s u m i n g   t h e   a n g l e s   a r e   i n   r a d i a n s .  
 	 d o u b l e   c 1   =   c o s ( y   /   2 ) ;  
 	 d o u b l e   s 1   =   s i n ( y   /   2 ) ;  
 	 d o u b l e   c 2   =   c o s ( z   /   2 ) ;  
 	 d o u b l e   s 2   =   s i n ( z   /   2 ) ;  
 	 d o u b l e   c 3   =   c o s ( x   /   2 ) ;  
 	 d o u b l e   s 3   =   s i n ( x   /   2 ) ;  
 	 d o u b l e   c 1 c 2   =   c 1 * c 2 ;  
 	 d o u b l e   s 1 s 2   =   s 1 * s 2 ;  
 	 f l o a t   q w   =   c 1 c 2 * c 3   -   s 1 s 2 * s 3 ;  
 	 f l o a t   q x   =   c 1 c 2 * s 3   +   s 1 s 2 * c 3 ;  
 	 f l o a t   q y   =   s 1 * c 2 * c 3   +   c 1 * s 2 * s 3 ;  
 	 f l o a t   q z   =   c 1 * s 2 * c 3   -   s 1 * c 2 * s 3 ;  
  
 	 q u a r t e r n i o n [ 0 ]   =   q w ;  
 	 q u a r t e r n i o n [ 1 ]   =   q x ;  
 	 q u a r t e r n i o n [ 2 ]   =   q y ;  
 	 q u a r t e r n i o n [ 3 ]   =   q z ;  
 }  
  
 v o i d   Q u a t e r n i o n M u l t i V e c t o r ( f l o a t *   q u a t ,   f l o a t *   v e c ,   f l o a t *   r e s u l t ) {  
 	 f l o a t   n u m   =   q u a t [ 1 ]   *   2 ;  
 	 f l o a t   n u m 2   =   q u a t [ 2 ]   *   2 ;  
 	 f l o a t   n u m 3   =   q u a t [ 3 ]   *   2 ;  
 	 f l o a t   n u m 4   =   q u a t [ 1 ]   *   n u m ;  
 	 f l o a t   n u m 5   =   q u a t [ 2 ]   *   n u m 2 ;  
 	 f l o a t   n u m 6   =   q u a t [ 3 ]   *   n u m 3 ;  
 	 f l o a t   n u m 7   =   q u a t [ 1 ]   *   n u m 2 ;  
 	 f l o a t   n u m 8   =   q u a t [ 1 ]   *   n u m 3 ;  
 	 f l o a t   n u m 9   =   q u a t [ 2 ]   *   n u m 3 ;  
 	 f l o a t   n u m 1 0   =   q u a t [ 0 ]   *   n u m ;  
 	 f l o a t   n u m 1 1   =   q u a t [ 0 ]   *   n u m 2 ;  
 	 f l o a t   n u m 1 2   =   q u a t [ 0 ]   *   n u m 3 ;  
 	  
 	 r e s u l t [ 0 ]   =   ( 1   -   ( n u m 5   +   n u m 6 ) )   *   v e c [ 0 ]   +   ( n u m 7   -   n u m 1 2 )   *   v e c [ 1 ]   +   ( n u m 8   +   n u m 1 1 )   *   v e c [ 2 ] ;  
 	 r e s u l t [ 1 ]   =   ( n u m 7   +   n u m 1 2 )   *   v e c [ 0 ]   +   ( 1   -   ( n u m 4   +   n u m 6 ) )   *   v e c [ 1 ]   +   ( n u m 9   -   n u m 1 0 )   *   v e c [ 2 ] ;  
 	 r e s u l t [ 2 ]   =   ( n u m 8   -   n u m 1 1 )   *   v e c [ 0 ]   +   ( n u m 9   +   n u m 1 0 )   *   v e c [ 1 ]   +   ( 1   -   ( n u m 4   +   n u m 5 ) )   *   v e c [ 2 ] ;  
 }  
  
 f l o a t   V e c t o r D o t ( f l o a t *   v e c 1 ,   f l o a t *   v e c 2 )  
 {  
 	 f l o a t   r e s u l t ;  
  
 	 r e s u l t   =   v e c 1 [ 0 ]   *   v e c 2 [ 0 ]   +   v e c 1 [ 1 ]   *   v e c 2 [ 1 ]   +   v e c 1 [ 2 ]   *   v e c 2 [ 2 ] ;  
  
 	 r e t u r n   r e s u l t ;  
 }  
  
 v o i d   V e c t o r C r o s s ( f l o a t *   v e c 1 ,   f l o a t *   v e c 2 ,   f l o a t *   r e s u l t )  
 {  
 	 r e s u l t [ 0 ]   =   v e c 1 [ 1 ]   *   v e c 2 [ 2 ]   -   v e c 1 [ 2 ]   *   v e c 2 [ 1 ] ;  
 	 r e s u l t [ 1 ]   =   v e c 1 [ 2 ]   *   v e c 2 [ 0 ]   -   v e c 1 [ 0 ]   *   v e c 2 [ 2 ] ;  
 	 r e s u l t [ 2 ]   =   v e c 1 [ 0 ]   *   v e c 2 [ 1 ]   -   v e c 1 [ 1 ]   *   v e c 2 [ 0 ] ;  
 }  
  
 v o i d   V e c t o r N o r m a l i z e ( f l o a t *   v e c 1 ,   f l o a t *   r e s u l t )  
 {  
 	 f l o a t   m a g n i t u d e   =   V e c t o r M a g n i t u d e ( v e c 1 ) ;  
  
 	 r e s u l t [ 0 ]   =   v e c 1 [ 0 ]   /   m a g n i t u d e ;  
 	 r e s u l t [ 1 ]   =   v e c 1 [ 1 ]   /   m a g n i t u d e ;  
 	 r e s u l t [ 2 ]   =   v e c 1 [ 2 ]   /   m a g n i t u d e ;  
 }  
  
 f l o a t   V e c t o r M a g n i t u d e ( f l o a t *   v e c 1 )  
 {  
 	 f l o a t   m a g n i t u d e   =   s q r t ( v e c 1 [ 0 ]   *   v e c 1 [ 0 ]   +   v e c 1 [ 1 ]   *   v e c 1 [ 1 ]   +   v e c 1 [ 2 ]   *   v e c 1 [ 2 ] ) ;  
 	 r e t u r n   m a g n i t u d e ;  
 }  
  
 v o i d   V e c t o r S c a l e r M u l t i p l y ( f l o a t   s ,   f l o a t *   v e c 1 ,   f l o a t *   r e s u l t )  
 {  
 	 r e s u l t [ 0 ]   =   s * v e c 1 [ 0 ] ;  
 	 r e s u l t [ 1 ]   =   s * v e c 1 [ 1 ] ;  
 	 r e s u l t [ 2 ]   =   s * v e c 1 [ 2 ] ;  
 }  
  
 f l o a t   C l a m p A n g l e ( f l o a t   a n g l e ,   f l o a t   m i n ,   f l o a t   m a x )  
 {  
 	 i f   ( a n g l e   <   - 3 6 0 . 0 F )  
 	 	 a n g l e   + =   3 6 0 . 0 F ;  
 	 i f   ( a n g l e   >   3 6 0 . 0 F )  
 	 	 a n g l e   - =   3 6 0 . 0 F ;  
  
 	 f l o a t   r e s u l t   =   a n g l e ;  
  
 	 i f   ( a n g l e   >   m a x )  
 	 	 r e s u l t   =   m a x ;  
 	 i f   ( a n g l e   <   m i n )  
 	 	 r e s u l t   =   m i n ;  
 	 r e t u r n   r e s u l t ;  
 }  
  
 / * - - - - - - - - - - - - - - - - - -  
 m o v e m e n t   c o n t r o l  
 - - - - - - - - - - - - - - - - - - - * /  
 v o i d   M o v e m e n t ( B Y T E   c o d e ,   B O O L 4   v a l u e )  
 {  
 	 / /   H o m e w o r k   # 0 1   p a r t   2  
 	 F n C h a r a c t e r   a c t o r ;  
 	 a c t o r . I D ( a c t o r I D ) ;  
 	 i f   ( c o d e   = =   F Y _ U P   | |   c o d e   = =   F Y _ D O W N   | |   c o d e   = =   F Y _ L E F T   | |   c o d e   = =   F Y _ R I G H T )  
 	 {  
 	 	 i f   ( v a l u e )  
 	 	 	 a c t o r . S e t C u r r e n t A c t i o n ( N U L L ,   0 ,   r u n I D ,   5 . 0 f ) ;  
 	 	 e l s e   i f   ( ! ( F y C h e c k H o t K e y S t a t u s ( F Y _ U P )   | |   F y C h e c k H o t K e y S t a t u s ( F Y _ D O W N )   | |   F y C h e c k H o t K e y S t a t u s ( F Y _ L E F T )   | |   F y C h e c k H o t K e y S t a t u s ( F Y _ R I G H T ) ) )  
 	 	 	 a c t o r . S e t C u r r e n t A c t i o n ( N U L L ,   0 ,   i d l e I D ,   5 . 0 f ) ;  
 	 }  
  
 	 i f   ( c o d e   = =   F Y _ U P )  
 	 {  
 	 	 i f   ( v a l u e   = =   f a l s e )  
 	 	 {  
 	 	 	 u p _ f i r s t P r e s s e d   =   f a l s e ;  
 	 	 }  
 	 }  
  
 	 i f   ( c o d e   = =   F Y _ D O W N )  
 	 {  
 	 	 i f   ( v a l u e   = =   f a l s e )  
 	 	 {  
 	 	 	 d o w n _ f i r s t P r e s s e d   =   f a l s e ;  
 	 	 }  
 	 }  
  
 	 i f   ( c o d e   = =   F Y _ L E F T )  
 	 {  
 	 	 i f   ( v a l u e   = =   f a l s e )  
 	 	 {  
 	 	 	 l e f t _ f i r s t P r e s s e d   =   f a l s e ;  
 	 	 }  
 	 }  
  
 	 i f   ( c o d e   = =   F Y _ R I G H T )  
 	 {  
 	 	 i f   ( v a l u e   = =   f a l s e )  
 	 	 {  
 	 	 	 r i g h t _ f i r s t P r e s s e d   =   f a l s e ;  
 	 	 }  
 	 }  
 	 / /   . . . .  
 }  
  
  
 / * - - - - - - - - - - - - - - - - - -  
 q u i t   t h e   d e m o  
 C . W a n g   0 3 2 7 ,   2 0 0 5  
 - - - - - - - - - - - - - - - - - - - * /  
 v o i d   Q u i t G a m e ( B Y T E   c o d e ,   B O O L 4   v a l u e )  
 {  
 	 i f   ( c o d e   = =   F Y _ E S C A P E )   {  
 	 	 i f   ( v a l u e )   {  
 	 	 	 F y Q u i t F l y W i n 3 2 ( ) ;  
 	 	 }  
 	 }  
 }  
  
  
  
 / * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  
 i n i t i a l i z e   t h e   p i v o t   o f   t h e   c a m e r a  
 C . W a n g   0 3 2 9 ,   2 0 0 5  
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - * /  
 v o i d   I n i t P i v o t ( i n t   x ,   i n t   y )  
 {  
 	 o l d X   =   x ;  
 	 o l d Y   =   y ;  
 	 f r a m e   =   0 ;  
 }  
  
  
 / * - - - - - - - - - - - - - - - - - -  
 p i v o t   t h e   c a m e r a  
 C . W a n g   0 3 2 9 ,   2 0 0 5  
 - - - - - - - - - - - - - - - - - - - * /  
 v o i d   P i v o t C a m ( i n t   x ,   i n t   y )  
 {  
 	 F n O b j e c t   m o d e l ;  
  
 	 i f   ( x   ! =   o l d X )   {  
 	 	 m o d e l . I D ( c I D ) ;  
 	 	 m o d e l . R o t a t e ( Z _ A X I S ,   ( f l o a t ) ( x   -   o l d X ) ,   G L O B A L ) ;  
 	 	 o l d X   =   x ;  
 	 }  
  
 	 i f   ( y   ! =   o l d Y )   {  
 	 	 m o d e l . I D ( c I D ) ;  
 	 	 m o d e l . R o t a t e ( X _ A X I S ,   ( f l o a t ) ( y   -   o l d Y ) ,   G L O B A L ) ;  
 	 	 o l d Y   =   y ;  
 	 }  
 }  
  
  
 / * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  
 i n i t i a l i z e   t h e   m o v e   o f   t h e   c a m e r a  
 C . W a n g   0 3 2 9 ,   2 0 0 5  
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - * /  
 v o i d   I n i t M o v e ( i n t   x ,   i n t   y )  
 {  
 	 o l d X M   =   x ;  
 	 o l d Y M   =   y ;  
 	 f r a m e   =   0 ;  
 }  
  
  
 / * - - - - - - - - - - - - - - - - - -  
 m o v e   t h e   c a m e r a  
 C . W a n g   0 3 2 9 ,   2 0 0 5  
 - - - - - - - - - - - - - - - - - - - * /  
 v o i d   M o v e C a m ( i n t   x ,   i n t   y )  
 {  
 	 i f   ( x   ! =   o l d X M )   {  
 	 	 F n O b j e c t   m o d e l ;  
  
 	 	 m o d e l . I D ( c I D ) ;  
 	 	 m o d e l . T r a n s l a t e ( ( f l o a t ) ( x   -   o l d X M ) * 2 . 0 f ,   0 . 0 f ,   0 . 0 f ,   L O C A L ) ;  
 	 	 o l d X M   =   x ;  
 	 }  
 	 i f   ( y   ! =   o l d Y M )   {  
 	 	 F n O b j e c t   m o d e l ;  
  
 	 	 m o d e l . I D ( c I D ) ;  
 	 	 m o d e l . T r a n s l a t e ( 0 . 0 f ,   ( f l o a t ) ( o l d Y M   -   y ) * 2 . 0 f ,   0 . 0 f ,   L O C A L ) ;  
 	 	 o l d Y M   =   y ;  
 	 }  
 }  
  
  
 / * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  
 i n i t i a l i z e   t h e   z o o m   o f   t h e   c a m e r a  
 C . W a n g   0 3 2 9 ,   2 0 0 5  
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - * /  
 v o i d   I n i t Z o o m ( i n t   x ,   i n t   y )  
 {  
 	 o l d X M M   =   x ;  
 	 o l d Y M M   =   y ;  
 	 f r a m e   =   0 ;  
 }  
  
  
 / * - - - - - - - - - - - - - - - - - -  
 z o o m   t h e   c a m e r a  
 C . W a n g   0 3 2 9 ,   2 0 0 5  
 - - - - - - - - - - - - - - - - - - - * /  
 v o i d   Z o o m C a m ( i n t   x ,   i n t   y )  
 {  
 	 i f   ( x   ! =   o l d X M M   | |   y   ! =   o l d Y M M )   {  
 	 	 F n O b j e c t   m o d e l ;  
  
 	 	 m o d e l . I D ( c I D ) ;  
 	 	 m o d e l . T r a n s l a t e ( 0 . 0 f ,   0 . 0 f ,   ( f l o a t ) ( x   -   o l d X M M ) * 1 0 . 0 f ,   L O C A L ) ;  
 	 	 o l d X M M   =   x ;  
 	 	 o l d Y M M   =   y ;  
 	 }  
 }  
  
  
 v o i d   R o t a t e C a m ( i n t   x ,   i n t   y )  
 {  
 	 f l o a t   a x i s _ x   =   0 ;  
 	 f l o a t   a x i s _ y   =   0 ;  
 	 i f   ( x   ! =   o l d X M )   {  
 	 	 i f   ( ( f l o a t ) ( x   -   o l d X M )   >   0 )  
 	 	 	 a x i s _ x   =   1 ;  
 	 	 e l s e  
 	 	 	 a x i s _ x   =   - 1 ;  
  
 	 	 o l d X M   =   x ;  
 	 }  
 	 i f   ( y   ! =   o l d Y M )   {  
 	 	 i f   ( ( f l o a t ) ( y   -   o l d Y M )   >   0 )  
 	 	 	 a x i s _ y   =   1 ;  
 	 	 e l s e  
 	 	 	 a x i s _ y   =   - 1 ;  
  
 	 	 o l d Y M   =   y ;  
 	 }  
  
  
 	 r o t _ x   + =   a x i s _ x * x S p e e d * 0 . 0 2 ;  
 	 r o t _ y   + =   a x i s _ y * y S p e e d * 0 . 0 2 ;  
  
 	 r o t _ x   =   C l a m p A n g l e ( r o t _ x ,   - 8 0 ,   8 0 ) ;  
 	 r o t _ y   =   C l a m p A n g l e ( r o t _ y ,   - 8 0 ,   2 0 ) ;  
 }  
  
 v o i d   I n i t Z o o m 2 ( i n t   x ,   i n t   y )  
 {  
 	 o l d X M M   =   x ;  
 	 o l d Y M M   =   y ;  
 	 f r a m e   =   0 ;  
 }  
  
 v o i d   Z o o m C a m 2 ( i n t   x ,   i n t   y )  
 {  
 	 i f   ( x   ! =   o l d X M M   | |   y   ! =   o l d Y M M )   {  
  
 	 	 d i s t a n c e   + =   ( f l o a t ) ( x   -   o l d X M M ) * 1 0 . 0 f ;  
  
 	 	 o l d X M M   =   x ;  
 	 	 o l d Y M M   =   y ;  
 	 }  
 } 