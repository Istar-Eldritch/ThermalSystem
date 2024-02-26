modded class PrepareFish
{	
	override void Do(ItemBase ingredients[], PlayerBase player,array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
        super.Do(ingredients, player, results, specialty_weight);

		ItemBase ingredient = ingredients[0];
		float temp = ingredient.GetTemperature();

		for (int i=0; i < results.Count(); i++)
		{
			ItemBase item_result;
			Class.CastTo(item_result, results.Get(i));
            item_result.SetTemperature(temp);
		}
	}
};
