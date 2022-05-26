class Img:
    def __init__(self,r,c):
            self.c = c
            self.r = r
            self.img = [0]*r*c

            self.lns = (lambda p: [
                [
                    self.ln(r-round(p[i+1]/p[i+3]),
                    round(p[i]/p[i+3]),
                    r-round(p[i+5]/p[i+7]),
                    round(p[i+4]/p[i+7]),16741235)
                    for i in range(0,len(p),8)
                ],self][1])

            # self.lns() == self??

            self.ln = (lambda rs,cs,rf,cf,v,e=[0,0]:
                self.ln(rf,cf,rs,cs,v) if (rs>rf if abs(rf-rs) < abs(cf-cs)else cs>cf)else([asg(e,rs,1),asg(e,2*abs(rf-rs)-abs(cf-cs)),[[self.s(e[1],c,v),asg(e,e[1]+1,1),asg(e,e[0]+2*abs(rf-rs)-2*abs(cf-cs))]if 0<e[0]else[self.s(e[1],c,v),0,asg(e,e[0]+2*abs(rf-rs))]for c in range(cs,cf-1 if cs>cf else cf+1,-1 if cs>cf else 1)]]if abs(rf-rs)<abs(cf-cs)else[asg(e,cs,1),asg(e,2*abs(cf-cs)-abs(rf-rs)),[[self.s(r,e[1],v),asg(e,e[1]+1,1),asg(e,e[0]+2*abs(cf-cs)-2*abs(rf-rs))]if 0<e[0]else[self.s(r,e[1],v),0,asg(e,e[0]+2*abs(cf-cs))]for r in range(rs,rf-1 if rs>rf else rf+1,-1 if rs>rf else 1)]]))

            self.s = (lambda r,c,v:
                [asg(self.img,v,c+r*self.c)] if -1 < r < self.r and -1 < c < self.c else 0)
            
            self.oof = (lambda:"P3 "+str(self.c)+" "+str(self.r)+" 255\n"+" ".join(str(round(i/65536))+" "+str(round(i/256)%256)+" "+str(i%256) for i in self.img))
