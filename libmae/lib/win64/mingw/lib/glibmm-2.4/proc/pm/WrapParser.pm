# gtkmm - WrapParser module
#
# Copyright 2001 Free Software Foundation
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or 
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
# GNU General Public License for more details. 
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
#
package WrapParser;
use strict;
use warnings;
use Util;
use GtkDefs;
use Function;
use DocsParser;

BEGIN {
     use Exporter   ();
     our ($VERSION, @ISA, @EXPORT, @EXPORT_OK, %EXPORT_TAGS);

     # set the version for version checking
     $VERSION     = 1.00;
     @ISA         = qw(Exporter);
     @EXPORT      = ( );
     %EXPORT_TAGS = ( );
     # your exported package globals go here,
     # as well as any optionally exported functions
     @EXPORT_OK   = ( );
     }
our @EXPORT_OK;

############################################################################

my @tokens = ();

# $objWrapParser new($objOutputter)
sub new($)
{
  my ($objOutputter) = @_;

  my $self = {};
  bless $self;

   #Initialize member data:
  $$self{objOutputter} = $objOutputter;
  $$self{filename} = "(none)";
  $$self{line_num} = 0;

  $$self{level} = 0;
  $$self{class} = "";
  $$self{c_class} = "";
  $$self{in_class} = 0;
  $$self{first_namespace} = 1;
  $$self{namespace} = [];
  $$self{in_namespace} = [];

  $$self{defsdir} = ".";

  $$self{module} = ""; #e.g. "gtkmm"

  $$self{type} = "GTKOBJECT"; # or "BOXEDTYPE", or "GOBJECT" - wrapped differently.

  return $self;
}

# void parse_and_build_output()
sub parse_and_build_output($)
{
  my ($self) = @_;

  my $objOutputter = $$self{objOutputter};

  # Parse the tokens.
  my $token;
  while ( scalar(@tokens) )
  {
    $token = $self->extract_token();
    my $bAppend = 1;

    # we need to monitor the depth of braces
    if ($token eq '{')         { $self->on_open_brace(); }
    if ($token eq '}')         { $self->on_close_brace(); $bAppend = 0;}

    # protect `' from the source file from m4
    if ($token eq "`")         { $objOutputter->append("`'__BT__`'"); next; }
    if ($token eq "'")         { $objOutputter->append("`'__FT__`'"); next; }

    if ($token eq '"')         { $objOutputter->append($self->on_string_literal()); next; }
    if ($token eq '//')        { $objOutputter->append($self->on_comment_cpp()); next; }
    if ($token eq '/*')        { $objOutputter->append($self->on_comment_c()); next; }
    if ($token eq '/**')       { $self->on_comment_doxygen(); next; }

    # handle #m4begin ... #m4end
    if ($token eq "#m4begin")  { $objOutputter->append($self->on_m4_section()); next;}

    # handle #m4 ... \n
    if ($token eq "#m4")       { $objOutputter->append($self->on_m4_line()); next;}

    if ($token eq "_DEFS")     { $self->on_defs(); next;} #Read the defs file.
    if ($token eq "_IGNORE")     { $self->on_ignore(); next;} #Ignore a function.
    if ($token eq "_IGNORE_SIGNAL")     { $self->on_ignore_signal(); next;} #Ignore a signal.
    if ($token eq "_WRAP_METHOD")     { $self->on_wrap_method(); next;}
    if ($token eq "_WRAP_METHOD_DOCS_ONLY")     { $self->on_wrap_method_docs_only(); next;}
    if ($token eq "_WRAP_CORBA_METHOD")     { $self->on_wrap_corba_method(); next;} #Used in libbonobo*mm.
    if ($token eq "_WRAP_SIGNAL") { $self->on_wrap_signal(0); next;}
    if ($token eq "_WRAP_PROPERTY") { $self->on_wrap_property(); next;}
    if ($token eq "_WRAP_VFUNC") { $self->on_wrap_vfunc(); next;}
    if ($token eq "_WRAP_CTOR")   { $self->on_wrap_ctor(); next;}
    if ($token eq "_WRAP_CREATE") { $self->on_wrap_create(); next;}

    if ($token eq "_WRAP_ENUM")   { $self->on_wrap_enum(); next;}
    if ($token eq "_WRAP_GERROR") { $self->on_wrap_gerror(); next;}
    if ($token eq "_IMPLEMENTS_INTERFACE") { $self->on_implements_interface(); next;}

    if ($token =~ m/\A_CLASS_/s)
    {
      $self->on_class($token);
      next;

      # e.g.:
      # _CLASS_GENERIC
      # _CLASS_GOBJECT
      # _CLASS_GTKOBJECT
      # _CLASS_BOXEDTYPE
      # _CLASS_BOXEDTYPE_STATIC
      # _CLASS_INTERFACE
      # _CLASS_OPAQUE_COPYABLE
      # _CLASS_OPAQUE_REFCOUNTED
    }

    if ($token eq "namespace") { $self->on_namespace() };

    # After all token manipulations
    if($bAppend)
    {
      $objOutputter->append($token);
    }
  }
}

sub error($$)
{
  my ($self, $format) = @_;

  $format = "$$self{filename}:$$self{line_num}: $format";
  printf STDERR $format,@_;
}

######################################################################
##### 1.1 parser subroutines

########################################
###  returns the next token, ignoring some stuff.
# $string extract_token()
sub extract_token($)
{
  my ($self) = @_;

  while ( scalar(@tokens) )
  {
    $_ = shift @tokens;

    # skip empty tokens
    next if ( !defined($_) or $_ eq "" );

    # eat line statements
    if (m/^#l (\S+)\n/)
    {
      $$self{line_num} = $1;
      next;
    }

    # eat file statements
    if (m/^#f (\S+)\n/)
    {
      $$self{filename} = $1;
      next;
    }

    return $_;
   }
     
  return "";
}

### Returns the next token, but does not remove it from the queue, so that
# extract_token will return it again.
# $string peek_token()
sub peek_token($)
{
  my ($self) = @_;

  while ( scalar(@tokens) )
  {
    $_ = $tokens[0];

    # skip empty tokens
    if(!defined($_) or $_ eq "")
    {
      shift @tokens;
    }
    # eat line statements
    elsif ( /^#l (\S+)\n/)
    {
      $$self{line_num} = $1;
      shift @tokens;
    }
    # eat file statements
    elsif ( /^#f (\S+)\n/)
    {
      $$self{filename} = $1;
      shift @tokens;
    }
    else
    {
      return $_;
    }
  }

  return "";
}

# bool tokens_remaining()
sub tokens_remaining($)
{
  my ($self) = @_;
  return $#tokens >= 0;
}


########################################
###  we pass strings literally with quote substitution
# void on_string_literal()
sub on_string_literal($)
{
  my ($self) = @_;

  my @out;
  push (@out, '"');
  while ( scalar(@tokens) )
  {
    $_ = $self->extract_token();
    if ($_ eq "`") { push(@out, "`'__BT__`'"); next; }
    if ($_ eq "'") { push(@out, "`'__FT__`'"); next; }
    push (@out, $_);

    return join("",@out) if ($_ eq '"');
  }

  my $line_num = $$self{line_num};
  my $filename = $$self{filename};
  print STDERR "$filename:$line_num: Hit eof while in string\n";
}


########################################
###  we pass comments literally with quote substitution
# void on_comment_cpp()
sub on_comment_cpp($)
{
  my ($self) = @_;

  my @out;
  push (@out,"//\`");
  while ( scalar(@tokens) )
  {
    $_ = $self->extract_token();
    if ($_ eq "`") { push(@out,"\'__BT__\`"); next; }
    if ($_ eq "'") { push(@out,"\'__FT__\`"); next; }
    if ($_ eq "\n")
    {
      push (@out,"\'\n");
      return join("",@out)
    }

    if ($_ =~ /^_[A-Z]+$/) {$_="_$_";}  # wipe out potential macros

    push (@out,$_);
  }
}


########################################
###  we pass C comments literally with quote substitution
# void on_comment_c()
sub on_comment_c($)
{
  my ($self) = @_;

  my @out;
  push (@out,"/*\`");
  while ( scalar(@tokens) )
  {
    $_ = $self->extract_token();
    if ($_ eq "`") { push(@out,"\'__BT__\`"); next; }
    if ($_ eq "'") { push(@out,"\'__FT__\`"); next; }
    if ($_ eq "*/")
    {
      push (@out,"\'*/");
      return join("",@out)
    }

    push (@out,$_);
  }
}

sub on_comment_doxygen($)
{
  my ($self) = @_;

  my $objOutputter = $$self{objOutputter};

  my @out;
  push (@out,"/**\`");
  while ( scalar(@tokens) )
  {
    $_ = $self->extract_token();
    if ($_ eq "`") { push(@out,"\'__BT__\`"); next; }
    if ($_ eq "'") { push(@out,"\'__FT__\`"); next; }

    if ($_ eq "*/")
    {
      push (@out,"\'*");
      $objOutputter->append(join("", @out));

      # Find next non-whitespace token, but remember whitespace so that we
      # can print it if the next real token is not _WRAP_SIGNAL
      my @whitespace;
      my $next_token = $self->peek_token();
      while ($next_token !~ /\S/)
      {
        push(@whitespace, $self->extract_token());
	$next_token = $self->peek_token();
      }

      # If the next token is a signal, do not close this comment, to merge
      # this doxygen comment with the one from the signal.
      if($next_token eq '_WRAP_SIGNAL')
      {
	# Extract token and process
	$self->extract_token();
	# Tell wrap_signal to merge automatically generated comment with
	# already existing comment. This is why we do not close the comment
	# here.
        $self->on_wrap_signal(1);
      }
      else
      {
        # Something other than signal follows, so close comment normally
        $objOutputter->append("/");
        # And append whitespace we ignored so far
        $objOutputter->append(join("", @whitespace));
        # Do not extract the token so that parse_and_build_output() will
        # process it.
      }

      last;
    }

    push (@out,$_);
  }
}


########################################
###  handle #m4begin ... #m4end
# we don't substitute ` or ' in #m4begin
# void on_m4_section()
sub on_m4_section($)
{
  my ($self) = @_;

  my @value;
  my $token;

  while ( scalar(@tokens) )
  {
    $token = $self->extract_token();
    return join("", @value) if ($token eq "#m4end");
    push(@value, $token);
  }

  my $line_num = $$self{line_num};
  my $filename = $$self{filename};
  print STDERR "$filename:$line_num: Hit eof looking for #m4end\n";
  next;
}


########################################
###  handle #m4 ... /n
# we don't substitute ` or ' in #m4
# void on_m4_line()
sub on_m4_line ($)
{
  my ($self) = @_;

  my @value;
  my $token;
  while ( scalar(@tokens) )
  {
    $token = $self->extract_token();
    push(@value,$token); # push first, so we don't eat the newline
    return join("",@value) if ($token eq "\n");
  }
}


########################################
# m4 needs to know when we entered a namespace
# void on_namespace()
sub on_namespace($)
{
  my ($self) = @_;
  my $objOutputter = $$self{objOutputter};

  my $number = 0;
  my $token;
  my $arg;

  # we need to peek ahead to figure out what type of namespace 
  # declaration this is.
  while ( $number <= $#tokens )
  {
    $token = $tokens[$number];
    $number++;
    next if (!defined($token) or $token eq "");
#      print "> $token\n";

    if ($token eq '{')
    {
      $arg = string_trim($arg);

      if ($$self{first_namespace})
      {
        $objOutputter->append("_SECTION(SECTION_HEADER2)\n");
        $$self{first_namespace} = 0;
      }

      $objOutputter->append("_NAMESPACE($arg)");
      unshift(@{$$self{namespace}}, $arg);
      unshift(@{$$self{in_namespace}}, $$self{level}+1);
      return;
    }

    next if ( $token =~ /^#[lf] \S+\n/);
    return if ($token eq ';');

    $arg .= $token; #concatenate
  }
}


########################################
###  we don't want to report every petty function as unwrapped
# void on_ignore($)
sub on_ignore($)
{
  my ($self) = @_;
  my $str = $self->extract_bracketed_text();
  my @args = split(/\s+|,/,$str);
  foreach (@args)
  {
    next if ($_ eq "");
    GtkDefs::lookup_function($_); #Pretend that we've used it.
  }
}

sub on_ignore_signal($)
{
  my ($self) = @_;
  my $str = $self->extract_bracketed_text();
  $str = string_trim($str);
  $str = string_unquote($str);
  my @args = split(/\s+|,/,$str);
  foreach (@args)
  {
    next if ($_ eq "");
    GtkDefs::lookup_signal($$self{c_class}, $_); #Pretend that we've used it.
  }
}

########################################
###  we have certain macros we need to insert at end of statements
# void on_class($, $strClassCommand)
sub on_class($$)
{
  my ($self, $class_command) = @_;

  my $objOutputter = $$self{objOutputter};

  $$self{in_class} = $$self{level};

  #Remember the type of wrapper required, so that we can append the correct _END_CLASS_* macro later.
  { 
    my $str = $class_command;
    $str =~ s/^_CLASS_//;
    $$self{type} = $str;
  }

  my $str = $self->extract_bracketed_text();
  my ($class, $c_class) = split(',',$str);
  $class = string_trim($class);
  $c_class = string_trim($c_class);

  $$self{class} = $class;
  $$self{c_class} = $c_class;

  my @back;
  push(@back, $class_command);
  push(@back, "($str)");
  
  # When we hit _CLASS, we walk backwards through the output to find "class"
  my $token;
  while ( scalar(@{$$objOutputter{out}}))
  {
    $token = pop @{$$objOutputter{out}};
    unshift(@back, $token);
    if ($token eq "class")
    {
      $objOutputter->append("_CLASS_START()");

      my $strBack = join("", @back);

      $objOutputter->append($strBack);
      return;
    }
  }

  $self->error("$class_command outside of class.\n");
  exit(-1);
}

# remove surround spaces from the string
sub trim($)
{
    my $string = shift;
    $string =~ s/^\s+//;
    $string =~ s/\s+$//;
    return $string;
}

# order to read the defs file
# void on_defs()
sub on_defs($)
{
  my ($self) = @_;

  my $str = $self->extract_bracketed_text();
  my ($module, $defsfile) = split(/,/, $str); #e.g. _DEFS(gtkmm,gtk), where gtkmm is the module name, and gtk is the defs file name.
  $module = trim($module);
  $defsfile = trim($defsfile);

  # $$self{section} = $section;  #Save it so that we can reuse it in read_defs_included.
  $$self{module} = $module; #Use it later in call to output_temp_g1().

  GtkDefs::read_defs("$$self{defsdir}", "$defsfile.defs");

  #Read the documentation too, so that we can merge it into the generated C++ code:
  my $docs_filename = $defsfile . "_docs.xml";
  my $docs_filename_override = $defsfile . "_docs_override.xml";
  DocsParser::read_defs("$$self{defsdir}", $docs_filename, $docs_filename_override);
}

# void on_open_brace()
sub on_open_brace($)
{
  my ($self) = @_;

  $$self{level}++;
}

# void on_close_brace($)
sub on_close_brace($)
{
  my ($self) = @_;
  my $objOutputter = $$self{objOutputter};

  #push(@out, "($$self{level})");

  $self->on_end_class()
    if ($$self{in_class} && $$self{in_class} == $$self{level});

  $objOutputter->append("}"); #We append it here instead of after we return, so that we can end the namespace after it.

  $self->on_end_namespace()
    if ( scalar(@{$$self{in_namespace}}) && (@{$$self{in_namespace}}[0] == $$self{level}) );

  $$self{level}--;
}


########################################
###  denote the end of a class
# void on_end_class($)
sub on_end_class($)
{
  my ($self) = @_;
  my $objOutputter = $$self{objOutputter};

  # Examine $$self{type}, which was set in on_class()
  # And append the _END_CLASS_* macro, which will, in turn, output the m4 code.
  {
    my $str = $$self{type};
    $objOutputter->append("`'_END_CLASS_$str()\n");
  }

  $$self{class} = "";
  $$self{c_class} = "";
  $$self{in_class} = 0;
}


########################################
###  
# void on_end_namespace($)
sub on_end_namespace($)
{
  my ($self) = @_;
  my $objOutputter = $$self{objOutputter};

  $objOutputter->append("`'_END_NAMESPACE()");
  shift( @{$$self{namespace}} );
  shift( @{$$self{in_namespace}} );
}


######################################################################
##### some utility subroutines

########################################
###  takes (\S+) from the tokens (smart)
# $string extract_bracketed_text()
sub extract_bracketed_text($)
{
  my ($self) = @_;

  my $level = 1;
  my $str = "";

  # Move to the first "(":
  while ( scalar(@tokens) )
    {
      my $t = $self->extract_token();
      last if ($t eq "(");
    }

  # Concatenate until the corresponding ")":
  while ( scalar(@tokens) )
    {
      my $t = $self->extract_token();
      $level++ if ($t eq "(");
      $level-- if ($t eq ")");

      return $str if (!$level);
      $str .= $t;
    }

  return "";
}


########################################
###  breaks up a string by commas (smart)
# @strings string_split_commas($string)
sub string_split_commas($)
{
  my ($in) = @_;

  my @out;
  my $level = 0;
  my $str = "";
  my @in = split(/([,()])/, $in);

  while ($#in > -1)
    {
      my $t = shift @in;

      next if ($t eq "");
      $level++ if ($t eq "(");
      $level-- if ($t eq ")");

      # skip , inside functions  Ie.  void (*)(int,int)
      if ( ($t eq ",") && !$level) 
        {
          push(@out, $str);
          $str="";
          next;
        }

      $str .= $t;
    }

  push(@out,$str);
  return @out;
}


########################################
###  reads in the preprocessor files
# we insert line and file directives for later stages
# void read_file()
sub read_file($$$)
{
  my ($self, $srcdir, $source) = @_;

  my $lineno = 1;
  my @in = ();

  if ( ! -r "${srcdir}/${source}.hg")
  {
    print "Unable to find header file $srcdir/$source.hg\n";
    exit(1);
  }

  # Read header file:
  open(FILE, "${srcdir}/${source}.hg");
  push(@in, "#f ${source}.hg\n");
  while (<FILE>)
    {
      push(@in, "#l $lineno\n");
      push(@in, $_);
      ++$lineno;
    }
  close(FILE);
  push(@in, "\n", "_SECTION(SECTION_SRC_CUSTOM)\n");

  # Source file is optional.
  if ( -r "${srcdir}/${source}.ccg")
  {
    open(FILE, "${srcdir}/${source}.ccg");
    $lineno = 1;
    push(@in, "#f ${source}.ccg\n");
    while (<FILE>)
      {
        push(@in, "#l $lineno\n");
        push(@in, $_);
        ++$lineno;
      }
    close(FILE);
  }

  my $strIn = join("", @in);

  # Break the file into tokens.  Token is
  #      any group of #, A to z, 0 to 9, _
  #      /**
  #      /*
  #      *.
  #      //
  #      any char proceeded by \
  #      symbols ;{}"`'()
  #      newline
  @tokens = split(/(\#[lf] \S+\n)|([#A-Za-z0-9_]+)|(\/\*\*)|(\/\*)|(\*\/)|(\/\/)|(\\.)|([;{}"'`()])|(\n)/,
                         $strIn);
}


sub class_prefix($)
{
  my ($self) = @_;

  my $str = $$self{class};
  $str =~ s/([a-z])([A-Z])/$1_$2/g;
  $str =~ tr/A-Z/a-z/;
  return $str;
}


######################################################################
##### 2.1 subroutines for _WRAP

########################################

# $bool check_for_eof()
sub check_for_eof($)
{
  my ($self) = @_;

  my $filename = $$self{filename};
  my $line_num = $$self{line_num};

  unless (scalar(@tokens))
  {
    print STDERR "$filename:$line_num:hit eof in _WRAP\n";
    return 0; #EOF
  }

  return 1; # No EOF
}

# Look back for a Doxygen comment.  If there is one,
# remove it from the output and return it as a string.
sub extract_preceding_documentation ($)
{
  my ($self) = @_;
  my $outputter = $$self{objOutputter};
  my $out = \@{$$outputter{out}};

  my $comment = '';

  if ($#$out >= 2)
  {
    # steal the last three tokens
    my @back = splice(@$out, -3);
    local $_ = join('', @back);

    # Check for /*[*!] ... */ or //[/!] comments.  The closing */ _must_
    # be the last token of the previous line.  Apart from this restriction,
    # anything else should work, including multi-line comments.

    if (m#\A/\s*\*(?:\*`|`!)(.+)'\*/\s*\z#s or m#\A\s*//`[/!](.+)'\s*\z#s)
    {
      $comment = '`' . $1;
      $comment =~ s/\s*$/'/;
    }
    else
    {
      # restore stolen tokens
      push(@$out, @back);
    }
  }

  return $comment;
}

# void on_wrap_method()
sub on_wrap_method($)
{
  my ($self) = @_;
  my $objOutputter = $$self{objOutputter};

  return unless ($self->check_for_eof());

  my $filename = $$self{filename};
  my $line_num = $$self{line_num};

  my $commentblock = $self->extract_preceding_documentation();
  my $str = $self->extract_bracketed_text();
  my @args = string_split_commas($str);

  my $entity_type = "method";

  unless ($$self{in_class})
    {
      print STDERR "$filename:$line_num:_WRAP macro encountered outside class\n";
      return;
    }

  my $objCfunc;
  my $objCppfunc;

  # handle first argument
  my $argCppMethodDecl = $args[0];
  if ($argCppMethodDecl !~ m/\S/s)
  {
    print STDERR "$filename:$line_num:_WRAP_METHOD: missing prototype\n";
    return;
  }

  #Parse the method decaration and build an object that holds the details:
  $objCppfunc = &Function::new($argCppMethodDecl, $self);

  # handle second argument:

  my $argCFunctionName = $args[1];
  $argCFunctionName = string_trim($argCFunctionName);

  #Get the c function's details:

  # Checks that it's not empty and that it contains no whitespace.
  if ($argCFunctionName =~ m/^\S+$/s)
  {
    #c-name. e.g. gtk_clist_set_column_title
    $objCfunc = GtkDefs::lookup_function($argCFunctionName);

    if(!$objCfunc) #If the lookup failed:
    {
      $objOutputter->output_wrap_failed($argCFunctionName, "method defs lookup failed (1)");
      return;
    }
  }

  # Extra stuff needed?
  $$objCfunc{deprecated} = "";
  my $deprecation_docs = "";
  my $ifdef;
  while($#args >= 2) # If the optional ref/err/deprecated arguments are there.
  {
    my $argRef = string_trim(pop @args);
    #print "debug arg=$argRef\n";
    if($argRef eq "refreturn")
    {
      $$objCfunc{rettype_needs_ref} = 1;
    }
    elsif($argRef eq "errthrow")
    {
      $$objCfunc{throw_any_errors} = 1;
    }
    elsif($argRef eq "constversion")
    {
      $$objCfunc{constversion} = 1;
    }
    elsif($argRef =~ /^deprecated(.*)/) #If deprecated is at the start.
    {
      $$objCfunc{deprecated} = "deprecated";

      if($1 ne "")
      {
        $deprecation_docs = string_unquote(string_trim($1));
      }
    }
    elsif($argRef =~ /^ifdef(.*)/) #If ifdef is at the start.
    {
    	$ifdef = $1;
    }
  }

  if ($commentblock ne '')
  {
    $commentblock = '  /**' . $commentblock . "\n   */\n";
  }
  else
  {
    $commentblock = DocsParser::lookup_documentation($argCFunctionName, $deprecation_docs);
  }

  $objOutputter->output_wrap_meth($filename, $line_num, $objCppfunc, $objCfunc, $argCppMethodDecl, $commentblock, $ifdef);
}

# void on_wrap_method_docs_only()
sub on_wrap_method_docs_only($)
{
  my ($self) = @_;
  my $objOutputter = $$self{objOutputter};

  return unless ($self->check_for_eof());

  my $filename = $$self{filename};
  my $line_num = $$self{line_num};

  my $str = $self->extract_bracketed_text();
  my @args = string_split_commas($str);

  my $entity_type = "method";

  if (!$$self{in_class})
    {
      print STDERR "$filename:$line_num:_WRAP macro encountered outside class\n";
      return;
    }

  my $objCfunc;

  # handle first argument
  my $argCFunctionName = $args[0];
  $argCFunctionName = string_trim($argCFunctionName);

  # Get the C function's details:

  # Checks that it's not empty or contains whitespace
  if ($argCFunctionName =~ m/^\S+$/s)
  {
    #c-name. e.g. gtk_clist_set_column_title
    $objCfunc = GtkDefs::lookup_function($argCFunctionName);

    if(!$objCfunc) #If the lookup failed:
    {
      $objOutputter->output_wrap_failed($argCFunctionName, "method defs lookup failed (1)");
      return;
    }
  }

  # Extra ref needed?
  while($#args >= 1) # If the optional ref/err arguments are there.
  {
    my $argRef = string_trim(pop @args);
    if($argRef eq "errthrow")
    {
      $$objCfunc{throw_any_errors} = 1;
    }
  }

  my $commentblock = "";
  $commentblock = DocsParser::lookup_documentation($argCFunctionName, "");

  $objOutputter->output_wrap_meth_docs_only($filename, $line_num, $commentblock);
}

sub on_wrap_ctor($)
{
  my ($self) = @_;
  my $objOutputter = $$self{objOutputter};

  if( !($self->check_for_eof()) )
  {
   return;
  }

  my $filename = $$self{filename};
  my $line_num = $$self{line_num};

  my $str = $self->extract_bracketed_text();
  my @args = string_split_commas($str);

  my $entity_type = "method";

  if (!$$self{in_class})
    {
      print STDERR "$filename:$line_num:_WRAP_CTOR macro encountered outside class\n";
      return;
    }

  my $objCfunc;
  my $objCppfunc;

  # handle first argument
  my $argCppMethodDecl = $args[0];
  if ($argCppMethodDecl !~ m/\S/s)
    {
      print STDERR "$filename:$line_num:_WRAP_CTOR: missing prototype\n";
      return;
    }

  #Parse the method decaration and build an object that holds the details:
  $objCppfunc = &Function::new_ctor($argCppMethodDecl, $self);

  # handle second argument:

  my $argCFunctionName = $args[1];
  $argCFunctionName = string_trim($argCFunctionName);

  #Get the C function's details:
  if ($argCFunctionName =~ m/^\S+$/s)
  {
    $objCfunc = GtkDefs::lookup_function($argCFunctionName); #c-name. e.g. gtk_clist_set_column_title
    if(!$objCfunc) #If the lookup failed:
    {
      $objOutputter->output_wrap_failed($argCFunctionName, "ctor defs lookup failed (2)");
      return;
    }
  }

  $objOutputter->output_wrap_ctor($filename, $line_num, $objCppfunc, $objCfunc, $argCppMethodDecl);
}

sub on_implements_interface($$)
{
  my ($self) = @_;
  
  if( !($self->check_for_eof()) )
  {
   return;
  }

  my $filename = $$self{filename};
  my $line_num = $$self{line_num};

  my $str = $self->extract_bracketed_text();
  my @args = string_split_commas($str);

  # handle first argument
  my $interface = $args[0];

  # Extra stuff needed?
  my $ifdef; 
  while($#args >= 1) # If the optional ref/err/deprecated arguments are there.
  {
  	my $argRef = string_trim(pop @args);
    if($argRef =~ /^ifdef(.*)/) #If ifdef is at the start.
    {
    	$ifdef = $1;
    }
  }
  my $objOutputter = $$self{objOutputter};
  $objOutputter->output_implements_interface($interface, $ifdef);	
} 

sub on_wrap_create($)
{
  my ($self) = @_;

  if( !($self->check_for_eof()) )
  {
    return;
  }

  my $str = $self->extract_bracketed_text();

  my $objOutputter = $$self{objOutputter};
  $objOutputter->output_wrap_create($str, $self);
}

sub on_wrap_signal($$)
{
  my ($self, $merge_doxycomment_with_previous) = @_;

  if( !($self->check_for_eof()) )
  {
    return;
  }

  my $str = $self->extract_bracketed_text();
  my @args = string_split_commas($str);

  #Get the arguments:
  my $argCppDecl = $args[0];
  my $argCName = $args[1];
  $argCName = string_trim($argCName);
  $argCName = string_unquote($argCName);

  my $bCustomDefaultHandler = 0;
  my $bNoDefaultHandler = 0;
  my $bCustomCCallback = 0;
  my $bRefreturn = 0;
  my $ifdef;
  
  while($#args >= 2) # If optional arguments are there.
  {
    my $argRef = string_trim(pop @args);
    if($argRef eq "custom_default_handler")
    {
      $bCustomDefaultHandler = 1;
    }

    if($argRef eq "no_default_handler")
    {
      $bNoDefaultHandler = 1;
    }

    if($argRef eq "custom_c_callback")
    {
      $bCustomCCallback = 1;
    }

    if($argRef eq "refreturn")
    {
      $bRefreturn = 1;
    }
    
  	elsif($argRef =~ /^ifdef(.*)/) #If ifdef is at the start.
    {
    	$ifdef = $1;
    }
  }


  $self->output_wrap_signal( $argCppDecl, $argCName, $$self{filename}, $$self{line_num}, $bCustomDefaultHandler, $bNoDefaultHandler, $bCustomCCallback, $bRefreturn, $ifdef, $merge_doxycomment_with_previous);
}

# void on_wrap_vfunc()
sub on_wrap_vfunc($)
{
  my ($self) = @_;

  if( !($self->check_for_eof()) )
  {
    return;
  }

  my $str = $self->extract_bracketed_text();
  my @args = string_split_commas($str);

  #Get the arguments:
  my $argCppDecl = $args[0];
  my $argCName = $args[1];
  $argCName = string_trim($argCName);
  $argCName = string_unquote($argCName);

  my $refreturn = 0;
  my $refreturn_ctype = 0;
  my $ifdef = "";

  # Extra ref needed?
  while($#args >= 2) # If the optional ref/err arguments are there.
  {
    my $argRef = string_trim(pop @args);

    if($argRef eq "refreturn")
      { $refreturn = 1; }
    elsif($argRef eq "refreturn_ctype")
      { $refreturn_ctype = 1; }
  elsif($argRef =~ /^ifdef(.*)/) #If ifdef is at the start.
    {
    	$ifdef = $1;
    }
  }

  $self->output_wrap_vfunc($argCppDecl, $argCName, $refreturn, $refreturn_ctype,
                           $$self{filename}, $$self{line_num}, $ifdef);
}

sub on_wrap_enum($)
{
  my ($self) = @_;

  return unless ($self->check_for_eof());

  my $outputter = $$self{objOutputter};
  my $comment = $self->extract_preceding_documentation();

  # get the arguments
  my @args = string_split_commas($self->extract_bracketed_text());

  my $cpp_type = string_trim(shift(@args));
  my $c_type   = string_trim(shift(@args));

  # The remaining elements in @args could be flags or s#^FOO_## substitutions.

  $outputter->output_wrap_enum(
      $$self{filename}, $$self{line_num}, $cpp_type, $c_type, $comment, @args);
}

sub on_wrap_gerror($)
{
  my ($self) = @_;

  return unless ($self->check_for_eof());

  # get the arguments
  my @args = string_split_commas($self->extract_bracketed_text());

  my $cpp_type = string_trim(shift(@args));
  my $c_enum   = string_trim(shift(@args));
  my $domain   = string_trim(shift(@args));

  # The remaining elements in @args could be flags or s#^FOO_## substitutions.

  $$self{objOutputter}->output_wrap_gerror(
      $$self{filename}, $$self{line_num}, $cpp_type, $c_enum, $domain, @args);
}

sub on_wrap_property($)
{
  my ($self) = @_;
  my $objOutputter = $$self{objOutputter};

  return unless ($self->check_for_eof());

  my $str = $self->extract_bracketed_text();
  my @args = string_split_commas($str);

  #Get the arguments:
  my $argPropertyName = $args[0];
  $argPropertyName = string_trim($argPropertyName);
  $argPropertyName = string_unquote($argPropertyName);

  #Convert the property name to a canonical form, as it is inside gobject.
  #Otherwise, gobject might not recognise the name, 
  #and we will not recognise the property name when we get notification that the value changes.
  $argPropertyName =~ tr/_/-/;

  my $argCppType = $args[1];
  $argCppType = string_trim($argCppType);
  $argCppType = string_unquote($argCppType);

  my $filename = $$self{filename};
  my $line_num = $$self{line_num};

  $objOutputter->output_wrap_property($filename, $line_num, $argPropertyName, $argCppType, $$self{c_class});
}


sub output_wrap_check($$$$$$)
{
  my ($self, $CppDecl, $signal_name, $filename, $line_num, $macro_name) = @_;

  #Some checks:

  unless ($$self{in_class})
  {
    print STDERR "$filename:$line_num: $macro_name macro encountered outside class\n";
    return 1;
  }
  if ($CppDecl !~ m/\S/s)
  {
    print STDERR "$filename:$line_num:$macro_name: missing prototype\n";
    return 1;
  }
  return '';
}

# void output_wrap($CppDecl, $signal_name, $filename, $line_num, $bCustomDefaultHandler, $bNoDefaultHandler, $bCustomCCallback, $bRefreturn)
# Also used for vfunc.
sub output_wrap_signal($$$$$$$$$)
{
  my ($self, $CppDecl, $signal_name, $filename, $line_num, $bCustomDefaultHandler, $bNoDefaultHandler, $bCustomCCallback, $bRefreturn, $ifdef, $merge_doxycomment_with_previous) = @_;
  
  #Some checks:
  return if ($self->output_wrap_check($CppDecl, $signal_name,
                                      $filename, $line_num, "_WRAP_SIGNAL"));
  # handle first argument

  #Parse the method decaration and build an object that holds the details:
  my $objCppSignal = &Function::new($CppDecl, $self);
  $$objCppSignal{class} = $$self{class}; #Remember the class name for use in Outputter::output_wrap_signal().


  # handle second argument:
  my $objCSignal = undef;

  my $objOutputter = $$self{objOutputter};

  #Get the c function's details:
  if ($signal_name ne '')
  {
    $objCSignal = GtkDefs::lookup_signal($$self{c_class}, $signal_name);

    # Check for failed lookup.
    if($objCSignal eq 0) 
    {
    print STDERR "$signal_name\n";
      $objOutputter->output_wrap_failed($signal_name, 
        " signal defs lookup failed");
      return;
    }
  }

  $objOutputter->output_wrap_sig_decl($filename, $line_num, $objCSignal, $objCppSignal, $signal_name, $bCustomCCallback, $ifdef, $merge_doxycomment_with_previous);

  if($bNoDefaultHandler eq 0)
  {
    $objOutputter->output_wrap_default_signal_handler_h($filename, $line_num, $objCppSignal, $objCSignal, $ifdef);

    my $bImplement = 1;
    if($bCustomDefaultHandler) { $bImplement = 0; }
    $objOutputter->output_wrap_default_signal_handler_cc($filename, $line_num, $objCppSignal, $objCSignal, $bImplement, $bCustomCCallback, $bRefreturn, $ifdef);
  }
}

# void output_wrap($CppDecl, $signal_name, $filename, $line_num)
# Also used for vfunc.
sub output_wrap_vfunc($$$$$$$$)
{
  my ($self, $CppDecl, $vfunc_name, $refreturn, $refreturn_ctype, $filename, $line_num, $ifdef) = @_;

  #Some checks:
  return if ($self->output_wrap_check($CppDecl, $vfunc_name, $filename, $line_num, '_WRAP_VFUNC'));

  # handle first argument

  #Parse the method decaration and build an object that holds the details:
  my $objCppVfunc = &Function::new($CppDecl, $self);


  # handle second argument:
  my $objCVfunc = undef;

  my $objOutputter = $$self{objOutputter};

  #Get the c function's details:
  if ($vfunc_name =~ m/^\S+$/s) # if it's not empty and contains no whitespace
  {
    $objCVfunc = GtkDefs::lookup_signal($$self{c_class},$vfunc_name);
    if(!$objCVfunc) #If the lookup failed:
    {
      $objOutputter->output_wrap_failed($vfunc_name, " vfunc defs lookup failed");
      return;
    }
  }

  # Write out the appropriate macros.
  # These macros are defined in vfunc.m4:

  $$objCppVfunc{rettype_needs_ref} = $refreturn;
  $$objCppVfunc{name} .= "_vfunc"; #All vfuncs should have the "_vfunc" prefix, and a separate easily-named invoker method.

  $$objCVfunc{rettype_needs_ref} = $refreturn_ctype;

  $objOutputter->output_wrap_vfunc_h($filename, $line_num, $objCppVfunc, $objCVfunc,$ifdef);
  $objOutputter->output_wrap_vfunc_cc($filename, $line_num, $objCppVfunc, $objCVfunc, $ifdef);
}

# give some sort of weights to sorting attibutes
sub byattrib() 
{
  my %attrib_value = (
     "virtual_impl" ,1,
     "virtual_decl" ,2,
     # "sig_impl"     ,3,
     "sig_decl"     ,4, 
     "meth"         ,5
  );
 
  # $a and $b are hidden parameters to a sorting function
  return $attrib_value{$b} <=> $attrib_value{$a}; 
}


# void on_wrap_corba_method()
sub on_wrap_corba_method($)
{
  my ($self) = @_;
  my $objOutputter = $$self{objOutputter};

  return unless ($self->check_for_eof());

  my $filename = $$self{filename};
  my $line_num = $$self{line_num};

  my $str = $self->extract_bracketed_text();
  my @args = string_split_commas($str);

  my $entity_type = "method";

  if (!$$self{in_class})
    {
      print STDERR "$filename:$line_num:_WRAP macro encountered outside class\n";
      return;
    }

  my $objCppfunc;

  # handle first argument
  my $argCppMethodDecl = $args[0];
  if ($argCppMethodDecl !~ m/\S/s)
  {
    print STDERR "$filename:$line_num:_WRAP_CORBA_METHOD: missing prototype\n";
    return;
  }

  # Parse the method decaration and build an object that holds the details:
  $objCppfunc = &Function::new($argCppMethodDecl, $self);
  $objOutputter->output_wrap_corba_method($filename, $line_num, $objCppfunc);
}


1; # return package loaded okay.
