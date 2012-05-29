#!/usr/bin/lua
-- script recvives:
-- monsterLife
-- currentMonsterLife
-- currentMonsterMana
-- monsterStrength

math.randomseed( os.time() )

function calc ()
    local lifeRatio = currentMonsterLife / monsterLife
    local myRandom  = math.random( 100 )

    if lifeRatio > 80 then
        if myRandom >= 0 and myRandom < 70 then
            return attack1()
        elseif myRandom >= 70 and myRandom < 90 then
            return attack2()
        else
            return attack3()
        end
    elseif lifeRatio > 50 then
        if  myRandom >= 0 and myRandom < 40 then
            return attack1()
        elseif myRandom >=40 and myRandom < 80 then
            return attack2()
        else
            return attack3()
        end
    else
        if myRandom >= 0 and myRandom < 20 then
            return attack1()
        elseif myRandom >= 20 and myRandom < 60 then
            return attack2()
        else
            return attack3()
        end
    end
end

function attack1()
   local damage = monsterStrength * math.random( 8, 12 ) * 0.1
   local critChance = 5
   if math.random( 100 ) <= critChance then
       damage = damage * 2;
   end
   return 0, damage, currentMonsterMana
end

function attack2()
   local damage = monsterStrength * math.random( 8, 12 ) * 0.15
   local critChance = 5
   if math.random( 100 ) <= critChance then
       damage = damage * 2;
   end
   if( currentMonsterMana < 5 ) then
       return attack1()
   else
       currentMonsterMana = currentMonsterMana - 5
       return 1, damage, currentMonsterMana
   end
end

function attack3()
   local damage = monsterStrength * math.random( 8, 12 ) * 0.2
   local critChance = 10
   if math.random( 100 ) <= critChance then
       damage = damage * 2;
   end
   if( currentMonsterMana < 10 ) then
       return attack2()
   else
       currentMonsterMana = currentMonsterMana - 10
       return 2, damage, currentMonsterMana
   end
end

return calc()
