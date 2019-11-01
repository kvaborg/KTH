defmodule Tenta20160610 do

  def once([]) do {0, 0} end
  def once([h|t]) do
    {sum, len} = once(t)
    {sum+h, len+1}
  end

  def ack(0, n) do n + 1 end
  def ack(m, 0) when m > 0 do
    ack(m - 1, 1)
  end
  def ack(m,n) when m > 0 and n > 0 do
    ack(m - 1, ack(m, n - 1))
  end

  #def eval([]) do 0 end
  #def eval(['+'|t]) do end
  
  def test_tree_single() do
    {:tree, 2, nil, nil}
  end
  def test_tree_iso() do
    {:tree, 1, {:tree, 2, {:tree, 4, nil, nil}, {:tree, 5, {:tree, 7, nil, nil}, {:tree, 8, nil, nil}}}, {:tree, 3, {:tree, 6, nil, nil}, nil}}
  end
  def test_tree_noiso() do
    {:tree, 2, {:tree, 1, {:tree, 5, nil, nil}, nil}, {:tree, 6, nil, nil}}
  end
  def test_tree_mirror() do
    {:tree, 6, {:tree, 5, {:tree, 1, nil, nil}, {:tree, 3, nil, nil}}, {:tree, 4, {:tree, 2, nil, nil}, nil}}
  end


  @type tree :: {:tree, integer(), tree(), tree()} | nil

  def isomorfic(nil, nil) do true end
  def isomorfic({:tree, _val, l1, r1}, {:tree, _val, l2, r2}) do 
    case isomorfic(l1,l2) do
      true ->
        case isomorfic(r1,r2) do
          true ->
            true
          _ ->
            false
        end
      _ ->
        false
    end
  end
  def isomorfic(_,_) do false end
  #  def isomorfic({:tree, _val, l1, r1}, nil) do false end
  #  def isomorfic(nil, {:tree, _val, l1, r1}) do false end

  def iso(nil, nil) do true end
  def iso({:tree, _, l1, r1}, {:tree, _, l2, r2}) do
    iso(l1,l2)
    iso(r1,r2)
  end
  def iso(_,_) do false end


  def mirror(nil) do nil end
  def mirror({:tree, val, left, right}) do
    {:tree, val, mirror(right), mirror(left)}
  end
    
end
