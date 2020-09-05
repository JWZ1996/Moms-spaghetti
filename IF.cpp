Command::Command() : Command([]() {})
{

};

Command::Command(const std::function<void()>& input) : f{input}
{

};
Command::Command(std::function<void()>&& input) : f{ std::move(input) }
{
	
};

void Command::run() 
{
	f();
};
IF::IF(IF&& input) : options{ std::move(input.options) }, bool_val{ input.bool_val }{}

IF::IF(bool input) : bool_val{ input } {}

IF& IF::set(const std::function<void()>& input)
{
	options.emplace(true, new Command(input));
	return *this;
};
IF& IF::els(const std::function<void()>& input)
{
	options.emplace(false, new Command(input));
	return *this;
};
IF&& IF::set( IF&& input)
{
	options.emplace( true, new IF(std::move(input)) );
	return std::forward<IF>(*this);
};
IF&& IF::els( IF&& input)
{
	options.emplace(true, new IF(std::move(input)) );
	return std::forward<IF>(*this);
};

void IF::run()
{
	if (options.find(bool_val) != options.end())
	{
		options[bool_val]->run();
	}
}