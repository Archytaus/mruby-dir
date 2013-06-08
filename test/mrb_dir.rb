assert 'entries' do
  entries = Dir.entries('.')

  assert_kind_of Array, entries
end

assert 'foreach' do
  Dir.foreach('.') do |file|
    assert_kind_of String, file
  end

  assert_kind_of Enumerable, Dir.foreach('.')
end

assert 'exists?' do
  assert_true Dir.exists?('.')
  assert_true Dir.exists?('..')

  assert_false Dir.exists?('something')
end