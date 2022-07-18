import pygame
import random    

FPS = 60   #更新頻率
WIDTH = 550   #寬度
HEIGHT = 660  #高度

#顏色
RED = (255,0,0)                   #紅色
BLUE = (0,0,255)                  #藍色
GREEN = (0,255,0)                 #綠色
WHITE = (255,255,225)             #白色
ORANGE = (255,175,0)              #橘色
YELLOW = (255,255,0)              #黃色
BRICKRED = (204,51,0)             #磚紅色
BACKGROUND_COLOR = (25,100,80)    #背景色

pygame.init()   #遊戲初始化
screen = pygame.display.set_mode((WIDTH,HEIGHT))  #設定視窗尺寸
pygame.display.set_caption("Shooting Game")       #設定視窗標題
clock = pygame.time.Clock()                       #控制時間，讓遊戲每次都一致

#字體
font_name = pygame.font.match_font('arial')         #字型arial
#設置文字的函式
def draw_text(surf , text , size , x , y , color):
  font = pygame.font.Font(font_name , size)         #設置字型與大小
  text_surface = font.render(text , True , color)   #設置文字內容和顏色(白色)
  text_rect = text_surface.get_rect()
  text_rect.centerx = x             #設置x軸位置
  text_rect.top = y                 #設置y軸位置
  surf.blit(text_surface , text_rect)

#新磚頭
def new_brick():
  b = Brick()
  all_sprites.add(b)
  bricks.add(b)

#畫出生命線
def draw_health(surf , health_point , x , y):
  if health_point < 0:
    health_point=0
  BAR_LENGTH = 100      #總長度
  BAR_HEIGHT = 10       #總高度
  fill = (health_point/100)*BAR_LENGTH                          #內部填滿長度
  fill_rect = pygame.Rect(x , y , fill , BAR_HEIGHT)            #裡面
  pygame.draw.rect(surf , YELLOW , fill_rect)                   #矩形(內部填滿)
  outline_rect = pygame.Rect(x , y , BAR_LENGTH , BAR_HEIGHT)   #外框
  pygame.draw.rect(surf , WHITE , outline_rect , 2)             #矩形(外框)

#畫出初始畫面
def draw_inti():
  draw_text(screen , 'Shooting Game' , 68 , WIDTH*0.5 , HEIGHT*0.25 , ORANGE)     #標題
  draw_text(screen , 'Press space and arrow key to shoot and move.' , 24 , WIDTH*0.5 , HEIGHT*0.5 , YELLOW)   #說明遊戲遊玩方法
  draw_text(screen , 'Press S to start.' , 26 , WIDTH/2 , HEIGHT*0.75 , WHITE)      #遊戲開始方式
  pygame.display.update()
  waiting = True
  while waiting:    #等待鍵盤案下去開始
    clock.tick(FPS)   #60 times per second
    for event in pygame.event.get():    #回傳所有事件
      if event.type == pygame.QUIT:
        pygame.quit()   #直接把遊戲結束
      elif event.type == pygame.KEYUP:  #當按下按鍵後，放開時執行
        if event.key == pygame.K_s:         #按的為S鍵時
          waiting = False #讓遊戲開始

#玩家Player
class Player(pygame.sprite.Sprite):
  #玩家初始化
  def __init__(self):
    pygame.sprite.Sprite.__init__(self)
    self.image = pygame.Surface((50,30))   #玩家寬度=50，長度=30
    self.image.fill(GREEN)    #玩家顏色為綠色(0,255,0)
    self.rect = self.image.get_rect()
    self.rect.centerx = WIDTH / 2         #將玩家初始化位置為為底部的中央位置
    self.rect.bottom = HEIGHT - 10
    self.speedx = 8         #玩家的移動單位長
    self.health = 5         #玩家一場總共有五條命

  #玩家移動更新
  def update(self):
    key_pressed = pygame.key.get_pressed()
    if key_pressed[pygame.K_RIGHT]:   #當按下右鍵時
      self.rect.x += self.speedx         #玩家往右移動
    if key_pressed[pygame.K_LEFT]:    #當按下左鍵時
      self.rect.x -= self.speedx         #玩家往左移動

    if self.rect.right > WIDTH:      #當玩家往右邊時，若移動範圍超過邊界，則繼續維持在最右邊
      self.rect.right = WIDTH
    if self.rect.left < 0:           #當玩家往左邊時，若移動範圍超過邊界，則繼續維持在最左邊
      self.rect.left = 0
  
  #玩家射擊
  def shoot(self):
    bullet = Bullet(self.rect.centerx , self.rect.top)     #將子彈出發位置設置在玩家x軸的中間，y軸的頂端
    all_sprites.add(bullet)
    bullets.add(bullet)

#磚塊Brick(目標物)
class Brick(pygame.sprite.Sprite):
  #磚塊初始化
  def __init__(self):
    pygame.sprite.Sprite.__init__(self)
    self.image = pygame.Surface((30,40))   #磚塊寬度=30，長度=40
    self.image.fill(BRICKRED)              #磚塊顏色為磚紅色(204,51,0)
    self.rect = self.image.get_rect()
    self.rect.x = random.randrange( 0 , WIDTH - self.rect.width )   #隨機決定磚頭初始的位置
    self.rect.y = random.randrange( -100 , -40 )
    self.speedx = random.randrange( -3 , 3 )    #控制x軸，讓磚塊隨機左、右或直線
    self.speedy = random.randrange( 2 , 10 )    #控制y軸，隨機決定磚塊掉落速度

  #磚塊移動更新
  def update(self):
    self.rect.x += self.speedx     #磚頭x軸移動
    self.rect.y += self.speedy     #磚頭y軸移動
    if self.rect.top > HEIGHT or self.rect.left > WIDTH or self.rect.right < 0:      #如果磚頭超出遊戲邊界
      #將磚頭相關參數重新設定
      self.rect.x = random.randrange( 0 , WIDTH - self.rect.width )   #隨機決定磚頭初始的位置
      self.rect.y = random.randrange( -100 , -40 )
      self.speedx = random.randrange( -3 , 3 )    #控制x軸，讓磚塊隨機左、右或直線
      self.speedy = random.randrange( 2 , 10 )    #控制y軸，隨機決定磚塊掉落速度

#子彈Bullet
class Bullet(pygame.sprite.Sprite):
  #子彈初始化
  def __init__(self,x,y):
    pygame.sprite.Sprite.__init__(self)
    self.image = pygame.Surface((10,20))   #子彈寬度=10，長度=20
    self.image.fill(ORANGE)      #子彈顏色為橘色(255,185,0)
    self.rect = self.image.get_rect()
    self.rect.centerx = x        #子彈x軸位置在玩家x軸的中間
    self.rect.centery = y        #子彈y軸位置在玩家y軸的頂端
    self.speedy = -10            #子彈以往上10單位的速度往上

  def update(self):
    self.rect.y += self.speedy   #子彈y軸移動  
    if self.rect.bottom < 0:     #判斷子彈底部是否超過上界
      self.kill()                #超過則破壞
      

show_inti = True
running = True
while running:
  if show_inti:
    draw_inti()      #畫出初始畫面
    show_inti = False
    all_sprites = pygame.sprite.Group()
    bricks = pygame.sprite.Group()
    bullets = pygame.sprite.Group()
    powers = pygame.sprite.Group()
    player = Player()
    all_sprites.add(player)
    for i in range(10):      #設定產生8個磚頭
      new_brick()
    score = 0               #將分數設為0
    shoot = 0
  
  clock.tick(FPS) #60 times per second
  #取得玩家輸入情形
  for event in pygame.event.get():    #回傳所有事件
    if event.type == pygame.QUIT:
      running = False
    elif event.type == pygame.KEYDOWN:
      if event.key == pygame.K_SPACE:    #按下空白鍵射擊
        player.shoot()
        shoot += 1


  #更新遊戲參數 
  all_sprites.update()
  hits = pygame.sprite.groupcollide(bricks , bullets , True , True)   #bullet被brick碰到後
  for hit in hits:        
    score += 1          #加1分
    new_brick()       #再產生一個brick
    if score%40==0 and player.health<5 and score/shoot>0.5 :    #每獲得40分且生命<5且命中率>0.5時
      player.health += 1                       #可增加1條命

  hits = pygame.sprite.spritecollide(player , bricks , True)      #player被brick砸到後
  for hit in hits:
    new_brick()                #再產生一個brick
    player.health -= 1         #玩家生命值-1
    if player.health == 0 :    #當玩家生命值=0時
      show_inti = True              #準備重新開始遊戲


  #設定顯示畫面
  screen.fill(BACKGROUND_COLOR)  #背景色(25,100,80)
  all_sprites.draw(screen)
  draw_text(screen , str(score) , 26 , WIDTH/2 , 15 , BLUE)  #顯示分數
  if shoot>0:
    draw_text(screen , str(round(score/shoot,3)) , 22 , 25 , 15 , BLUE)  #顯示命中率
  else:
    draw_text(screen , str(0.0) , 22 , 25 , 15 , BLUE)  #顯示命中率
  draw_text(screen , 'LIFE' , 14 , WIDTH-120 , 6.9 , WHITE)  #顯示LIFE在生命線旁
  draw_health(screen , player.health*20 , WIDTH-105 , 10)     #顯示生命線
  pygame.display.update()

pygame.quit()