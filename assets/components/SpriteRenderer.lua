SpriteRenderer = {
	sprite = "???",
	r = 255,
	g = 255,
	b = 255,
	a = 255,
	sorting_order = 0,

	OnStart = function(self)
		self.transform = self.actor:GetComponent("Transform")
	end,

	OnRender = function(self)
		--Debug.Log("Actor: " .. self.actor:GetName() .. " is rendering " .. self.sprite)
		Image.DrawUIEx(self.sprite, self.transform.x, self.transform.y, self.r, self.g, self.b, self.a, self.sorting_order)
	end
}

