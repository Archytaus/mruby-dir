module Dir
  def self.foreach(dirname, &block)
    if block_given?
      entries(dirname).each(&block)
    else
      return entries(dirname)
    end
  end
end