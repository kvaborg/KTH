defmodule Ten180607 do

  def fizzbuzz(n) do 
    fizzbuzz(1, n+1, 1, 1)
  end
  def fizzbuzz(last, last, _, _) do [] end
  def fizzbuzz(next, last, 3, 5) do
    [:fizzbuzz | fizzbuzz(next + 1, last, 1, 1)]
  end
  def fizzbuzz(next, last, 3, buzz) do
    [:fizz | fizzbuzz(next + 1, last, 1, buzz + 1)]
  end
  def fizzbuzz(next, last, fizz, 5) do
    [:buzz | fizzbuzz(next + 1, last, fizz + 1, 1)]
  end
  def fizzbuzz(next, last, fizz, buzz) do
    [next | fizzbuzz(next + 1, last, fizz + 1, buzz + 1)]
  end

  @type tree :: nil | {:tree, any(), tree(), tree()}

  def test_tree_balanced() do
    {:tree, 1, {:tree, 2, nil, nil}, {:tree, 3, nil, nil}}
  end
  def test_tree_unbalanced() do
    {:tree, 1, {:tree, 2, nil, nil}, {:tree, 3, {:tree, 4, {:tree, 5, nil, nil}, nil}, nil}}
  end

  def fairly(nil) do {:ok, 0} end
  def fairly({:tree, _, left, right}) do
    case fairly(left) do
      {:ok, l} ->
        case fairly(right) do
          {:ok, r} ->
            if(abs(l-r) <= 1) do
              {:ok, 1 + max(l,r)}
            else
              :no
            end
          :no ->
            :no
        end
      :no ->
        :no
    end
  end


    
end
