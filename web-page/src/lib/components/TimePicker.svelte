<script lang="ts">
	import State from '$lib/state';

	export let min: string;
	export let max: string;

	let from = min;
	let to = max;

	$: State.updateFrom(from);
	$: State.updateTo(to);
</script>

<div class="time-picker-grid">
	<div class="from">
		<label for="from">De:</label>
		<input
			type="date"
			id="from"
			value={from}
			{min}
			{max}
			on:change={(arg) => {
				console.log(arg);
			}}
		/>
	</div>
	<div class="to">
		<label for="to">Até:</label>
		<input type="date" id="to" value={to} {min} {max} />
	</div>
</div>

<style>
	.time-picker-grid {
		display: grid;
		justify-items: start;
		align-items: center;
		gap: 4px;
		grid-template-columns: 1fr 1fr;
		grid-template-rows: 32px;
	}

	.from {
		justify-self: end;
	}

	input {
		color: black;
	}

	label {
		justify-self: end;
	}
</style>
