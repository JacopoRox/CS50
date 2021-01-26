
Flag = Class{}

function Flag:init(map)

    self.x = map.tileWidth * 26.5 + 3
    self.y = map.mapHeight * map.tileWidth / 2 - 6 * map.tileHeight
    self.dy = 50

    self.spritesheet = love.graphics.newImage('graphics/spritesheet.png')

    self.animations = {
        ['flag'] = Animation({
            texture = self.texture,
            frames = {
                map.sprites[FLAG_1],
                map.sprites[FLAG_2],
                map.sprites[FLAG_1]
            },
            interval = 0.2
        
        })
    }
    self.animation = self.animations['flag']
end

function Flag:update(dt)
    if map.player:checkVictory() and self.y < map.tileHeight * ((map.mapHeight - 2) / 2) - map.tileHeight then
        self.y = self.y + self.dy * dt
    end
    self.animation:update(dt)
    self.currentframe = self.animation:getCurrentFrame()

end

function Flag:render(dt)
    love.graphics.draw(self.spritesheet, self.currentframe, self.x, self.y)
end